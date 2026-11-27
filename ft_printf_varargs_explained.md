# How `ft_printf("%d %s", 42, "hi")` actually works (x86_64 Linux)

Scope: 64-bit Linux, System V ABI (your school machines). Other systems (Mac arm64, Windows) do this differently.
The structure and numbers below were cross-checked against the System V ABI layout and compiler output.

---

## 0. Words you need

| Word | Meaning |
|---|---|
| **CPU register** | A tiny storage slot inside the CPU. Very fast, 8 bytes each, only a handful exist. Not in RAM. |
| **RAM / memory** | Where your program's data lives. Every byte has an address. |
| **Stack** | A region of RAM used for function calls. Each function call gets a chunk of it called a **stack frame** (its local variables, return address, etc.). |
| **Caller / callee** | Caller = `main`, who calls `ft_printf`. Callee = `ft_printf`. |
| **Value vs address** | `42` is a value. The address of `"hi"` is a number saying *where in RAM* the characters `h`,`i`,`\0` sit. |
| **Named parameter** | The ones before `...`. For you, only `s`. |
| **Variadic args** | The ones matched by `...`. |

---

## 1. The call, before it happens (the caller's job)

The compiler knows the prototype of `ft_printf`, so it sets up like this:

```
rdi = address of the string "%d %s"     (this is the named parameter s)
rsi = 42                                (1st variadic arg, the VALUE)
rdx = address of the string "hi"        (2nd variadic arg, an ADDRESS)
al  = 0                                 (how many float registers are used; none here)
```

- The six registers used for integer/pointer args, in order: `rdi, rsi, rdx, rcx, r8, r9`.
- Strings like `"hi"` live in a read-only part of your program's memory. Only their **address** goes in the register. The characters are never copied.
- If there are more than 6 args, the extra ones are **pushed on the stack by the caller** instead (see section 6).

Then the `call` instruction runs: it pushes the return address on the stack and jumps into `ft_printf`.

---

## 2. First thing inside `ft_printf`: the compiler's hidden prologue

Registers are temporary. The next function call (like `write`) will reuse `rdi`, `rsi`, `rdx` for its own arguments and overwrite them.

So because `ft_printf` has `...`, the compiler adds extra code at the very start of the function (you never write it) that **copies all the argument registers into memory**, inside `ft_printf`'s own stack frame. That block of memory is called the **register save area**.

```
register save area (in ft_printf's own stack frame)

offset  0 : copy of rdi  ->  address of "%d %s"   (the named param s)
offset  8 : copy of rsi  ->  42
offset 16 : copy of rdx  ->  address of "hi"
offset 24 : copy of rcx  ->  leftover junk, unused
offset 32 : copy of r8   ->  leftover junk, unused
offset 40 : copy of r9   ->  leftover junk, unused
offset 48 .. 176 : copies of the float registers xmm0..xmm7 (16 bytes each)
```

- It is a **copy**. The originals are still in the registers until something overwrites them.
- The compiler checks `al` here: if it's 0, it skips copying the float registers, so integer-only programs never touch the float unit.

---

## 3. `va_start(inputs, s)`

`va_start` does **not copy any arguments**. The copying was already done in section 2.

All it does is fill in `inputs`. On this platform `va_list` is a small struct with 4 fields:

```
gp_offset          = 8      where to read the next integer/pointer in the save area
fp_offset          = 48     where to read the next float in the save area
overflow_arg_area  = address of the first stack-passed arg (in the caller's stack)
reg_save_area      = address of the block from section 2
```

Why `gp_offset` starts at 8: it starts at `8 * (number of named integer params)`. You have one named param (`s`, in slot 0), so the variadic part starts at slot 1, offset 8.

That's the answer to "does it only look at the `...` part": yes, because `gp_offset` starts after the named ones. The second argument of `va_start` (the last named param) is how the compiler knows how many named ones to skip.

---

## 4. `va_arg` (each call)

`va_arg` is not a normal function. The compiler turns it into a few instructions placed right where you wrote it. The logic is:

```
if gp_offset < 48:
    read 8 bytes at (reg_save_area + gp_offset)
    gp_offset += 8
else:
    read 8 bytes at overflow_arg_area
    overflow_arg_area += 8
then use as many bytes as the requested type needs
```

For our call:

```
va_arg(inputs, int)
   gp_offset = 8  (< 48)  -> read slot at offset 8 -> 42 -> take the lower 4 bytes as int
   gp_offset becomes 16

va_arg(inputs, char *)
   gp_offset = 16 (< 48)  -> read slot at offset 16 -> address of "hi" -> use all 8 bytes as pointer
   gp_offset becomes 24
```

Then your code does `write(1, s, 1)` with that pointer and prints `h`, `i`.

---

## 5. Why the type you ask for matters

Each slot is 8 bytes, and `va_arg` just reads the slot as the type you name:

- Ask for `int` -> uses the lower 4 bytes. The ABI doesn't guarantee what's in the other 4 bytes.
- Ask for `unsigned long` where the caller passed an `int` -> you read all 8 bytes, including those 4 undefined ones.
- Ask for the wrong kind entirely (like a whole struct instead of a pointer) -> you read the wrong number of bytes and every later `va_arg` is off too.

Also, `char` arguments are promoted to `int` by the caller (C rule for variadic args). That's why `%c` uses `va_arg(inputs, int)`.

---

## 6. More than 6 arguments: the overflow area

Example: `ft_printf(s, a1, a2, a3, a4, a5, a6, a7, a8)`

```
rdi = s
rsi = a1, rdx = a2, rcx = a3, r8 = a4, r9 = a5     (5 variadic args fit in registers)
a6, a7, a8  -> pushed on the stack by the caller, never in registers
```

- The first 5 `va_arg` calls read the save area. After the 5th, `gp_offset` is 48, which means "registers used up".
- The 6th `va_arg` takes the `else` branch: it reads from `overflow_arg_area`, which points into the **caller's stack frame**, directly at `a6`. Then it moves the pointer 8 bytes forward to `a7`, and so on.
- The overflow area is **not copied**. It's read in place, where the caller put it.

That's why a `va_list` is only valid while the calling function is still alive.

---

## 7. What gets stored: the data itself or its address?

| Argument | What's in the slot |
|---|---|
| `int`, `unsigned`, `char` (as int) | The value itself |
| `char *` (`%s`), `void *` (`%p`), pointer to a struct | The **address**. What it points to is never copied |
| `double` | The value, in a float register / float slot (not covered in the mandatory part) |

---

## 8. What happens to the registers afterwards

- Registers are not "saved somewhere to be restored". They're just scratch space. After the prologue copied them, the CPU is free to use them for anything.
- Calling `write(1, s, 1)` puts its own values into `rdi`, `rsi`, `rdx`, so the original ones are gone.
- That's why `va_arg` reads the **copies in the save area**, never the registers directly.

---

## 9. How is the format string "detected"?

It isn't. `s` is simply the first parameter, so the compiler passes it in `rdi` by position. Your `while (*s)` loop and `if (*s == '%')` are what give it meaning as a format string. The compiler doesn't know or check it.

---

## 10. See it yourself

Write a tiny variadic function in a file `t.c`, then:

```
cc -S -O0 t.c      # produces t.s
```

Open `t.s`. Near the top of the variadic function you'll see:

- a `test %al, %al` followed by a jump (the float-register check)
- a series of `mov` instructions storing `rsi`, `rdx`, `rcx`, `r8`, `r9` into the stack frame

That's the register save area being built. The exact offsets vary between compilers.

---

## One-paragraph summary

The caller puts the first 6 integer/pointer args in `rdi, rsi, rdx, rcx, r8, r9` (extras go on the stack). At the start of `ft_printf`, hidden compiler code copies those registers into a block in its own stack frame (the register save area). `va_start` just fills a 4-field struct (`gp_offset`, `fp_offset`, `overflow_arg_area`, `reg_save_area`) with the starting positions, skipping the named params. Each `va_arg` reads the next 8-byte slot, either from the save area or, once those run out, from the caller's stack, and moves its position forward. Integers are stored as values, pointers as addresses.
