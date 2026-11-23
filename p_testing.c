#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "ft_printf.h"

void	check(int a, int b)
{
	if (a == b)
		printf("OK\n\n");
	else
		printf("KO (std=%d, ft=%d)\n\n", a, b);
}

void	test_one(char *title, char *format, void *p)
{
	int	a;
	int	b;

	printf("--- %s\n", title);
	printf("std: <");
	a = printf(format, p);
	printf(">\n");
	printf("ft : <");
	b = ft_printf(format, p);
	printf(">\n");
	check(a, b);
}

int	main(void)
{
	int		a;
	int		b;
	int		x = 42;
	char	c = 'z';
	char	*heap = malloc(10);
	char	*str = "hello";

	setvbuf(stdout, NULL, _IONBF, 0);

	test_one("p: NULL", "%p", NULL);
	test_one("p: stack int", "%p", &x);
	test_one("p: stack char", "%p", &c);
	test_one("p: heap (malloc)", "%p", heap);
	test_one("p: string literal", "%p", str);
	test_one("p: address 1", "%p", (void *)1);
	test_one("p: address 15 (f)", "%p", (void *)15);
	test_one("p: address 16 (10)", "%p", (void *)16);
	test_one("p: address 0x1000", "%p", (void *)0x1000);
	test_one("p: address 0xdeadbeef", "%p", (void *)0xdeadbeef);
	test_one("p: address 0x123456789abcdef", "%p", (void *)0x123456789abcdefUL);
	test_one("p: biggest (ULONG_MAX)", "%p", (void *)ULONG_MAX);
	test_one("p: LONG_MIN", "%p", (void *)LONG_MIN);
	test_one("p: text around", "ptr=[%p]!", &x);
	test_one("p: text around NULL", "ptr=[%p]!", NULL);

	printf("--- two %%p back to back\n");
	printf("std: <");
	a = printf("%p%p", (void *)16, (void *)255);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%p%p", (void *)16, (void *)255);
	printf(">\n");
	check(a, b);

	printf("--- NULL and non-NULL together\n");
	printf("std: <");
	a = printf("%p %p", NULL, (void *)255);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%p %p", NULL, (void *)255);
	printf(">\n");
	check(a, b);

	printf("--- mixed %%p %%s %%d %%x %%c\n");
	printf("std: <");
	a = printf("%p %s %d %x %c", &x, "mid", -5, 255u, 'k');
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%p %s %d %x %c", &x, "mid", -5, 255u, 'k');
	printf(">\n");
	check(a, b);

	printf("--- %%p then %%%%\n");
	printf("std: <");
	a = printf("%p%%", (void *)255);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%p%%", (void *)255);
	printf(">\n");
	check(a, b);

	free(heap);
	return (0);
}