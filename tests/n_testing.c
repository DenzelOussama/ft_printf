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

void	test_one(char *title, char *format, int n)
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

	test_one("d: zero", "%d", 0);
	test_one("d: positive", "%d", 42);
	test_one("d: negative", "%d", -42);
	test_one("d: one digit", "%d", 7);
	test_one("d: negative one digit", "%d", -7);
	test_one("d: 10 (zero inside)", "%d", 10);
	test_one("d: 1000", "%d", 1000);
	test_one("d: -1000", "%d", -1000);
	test_one("d: INT_MAX", "%d", INT_MAX);
	test_one("d: INT_MIN", "%d", INT_MIN);
	test_one("d: INT_MIN + 1", "%d", INT_MIN + 1);
	test_one("d: text around", "num=[%d]!", 123);
	test_one("d: text around negative", "num=[%d]!", -123);

	test_one("i: zero", "%i", 0);
	test_one("i: positive", "%i", 42);
	test_one("i: negative", "%i", -42);
	test_one("i: INT_MAX", "%i", INT_MAX);
	test_one("i: INT_MIN", "%i", INT_MIN);

	printf("--- two %%d back to back\n");
	printf("std: <");
	a = printf("%d%d", 12, -34);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%d%d", 12, -34);
	printf(">\n");
	check(a, b);

	printf("--- %%d %%i %%d with spaces\n");
	printf("std: <");
	a = printf("%d %i %d", 1, -2, 3);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%d %i %d", 1, -2, 3);
	printf(">\n");
	check(a, b);

	printf("--- mixed %%d %%s %%c\n");
	printf("std: <");
	a = printf("%d %s %c %d", 5, "mid", 'x', -9);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%d %s %c %d", 5, "mid", 'x', -9);
	printf(">\n");
	check(a, b);

	printf("--- %%d then %%%%\n");
	printf("std: <");
	a = printf("%d%%", 50);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%d%%", 50);
	printf(">\n");
	check(a, b);

	return (0);
}