#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

void	check(int a, int b)
{
	if (a == b)
		printf("OK\n\n");
	else
		printf("KO (std=%d, ft=%d)\n\n", a, b);
}

void	test_one(char *title, char *format, unsigned int n)
{
	int	a;
	int	b;

	printf("--- %s\n", title);
	printf("std: <");
	a = printf(format, n);
	printf(">\n");
	printf("ft : <");
	b = ft_printf(format, n);
	printf(">\n");
	check(a, b);
}

int	main(void)
{
	int	a;
	int	b;

	setvbuf(stdout, NULL, _IONBF, 0);

	test_one("x: zero", "%x", 0);
	test_one("x: 9 (last digit)", "%x", 9);
	test_one("x: 10 (a)", "%x", 10);
	test_one("x: 15 (f)", "%x", 15);
	test_one("x: 16 (10)", "%x", 16);
	test_one("x: 255 (ff)", "%x", 255);
	test_one("x: 256 (100)", "%x", 256);
	test_one("x: 4096 (1000)", "%x", 4096);
	test_one("x: 0xdeadbeef", "%x", 0xdeadbeef);
	test_one("x: INT_MAX", "%x", INT_MAX);
	test_one("x: INT_MAX + 1", "%x", (unsigned int)INT_MAX + 1);
	test_one("x: UINT_MAX", "%x", UINT_MAX);
	test_one("x: -1 given as unsigned", "%x", -1);
	test_one("x: INT_MIN given as unsigned", "%x", INT_MIN);
	test_one("x: text around", "hex=[%x]!", 255);

	test_one("X: zero", "%X", 0);
	test_one("X: 10 (A)", "%X", 10);
	test_one("X: 255 (FF)", "%X", 255);
	test_one("X: 0xdeadbeef", "%X", 0xdeadbeef);
	test_one("X: UINT_MAX", "%X", UINT_MAX);
	test_one("X: -1 given as unsigned", "%X", -1);
	test_one("X: text around", "HEX=[%X]!", 48879);

	printf("--- %%x and %%X together\n");
	printf("std: <");
	a = printf("%x %X", 48879u, 48879u);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%x %X", 48879u, 48879u);
	printf(">\n");
	check(a, b);

	printf("--- two %%x back to back\n");
	printf("std: <");
	a = printf("%x%x", 171u, 205u);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%x%x", 171u, 205u);
	printf(">\n");
	check(a, b);

	printf("--- mixed %%x %%d %%u %%s %%c\n");
	printf("std: <");
	a = printf("%x %d %u %s %c", 255u, -5, 7u, "mid", 'z');
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%x %d %u %s %c", 255u, -5, 7u, "mid", 'z');
	printf(">\n");
	check(a, b);

	printf("--- %%x then %%%%\n");
	printf("std: <");
	a = printf("%x%%", 255u);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%x%%", 255u);
	printf(">\n");
	check(a, b);

	return (0);
}