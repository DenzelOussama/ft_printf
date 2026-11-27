#include "ft_printf.h"
#include <limits.h>

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
	int a;
	int b;

	setvbuf(stdout, NULL, _IONBF, 0);

	test_one("u: zero", "%u", 0);
	test_one("u: one digit", "%u", 7);
	test_one("u: 42", "%u", 42);
	test_one("u: 10 (zero inside)", "%u", 10);
	test_one("u: 1000", "%u", 1000);
	test_one("u: INT_MAX", "%u", INT_MAX);
	test_one("u: INT_MAX + 1 (2147483648)", "%u", (unsigned int)INT_MAX + 1);
	test_one("u: UINT_MAX - 1", "%u", UINT_MAX - 1);
	test_one("u: UINT_MAX", "%u", UINT_MAX);
	test_one("u: -1 given as unsigned", "%u", -1);
	test_one("u: -42 given as unsigned", "%u", -42);
	test_one("u: INT_MIN given as unsigned", "%u", INT_MIN);
	test_one("u: text around", "num=[%u]!", 123);

	printf("--- two %%u back to back\n");
	printf("std: <");
	a = printf("%u%u", 12u, 34u);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%u%u", 12u, 34u);
	printf(">\n");
	check(a, b);

	printf("--- %%u %%d %%u (unsigned and signed mixed)\n");
	printf("std: <");
	a = printf("%u %d %u", 1u, -2, UINT_MAX);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%u %d %u", 1u, -2, UINT_MAX);
	printf(">\n");
	check(a, b);

	printf("--- mixed %%u %%s %%c\n");
	printf("std: <");
	a = printf("%u %s %c %u", 5u, "mid", 'x', 9u);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%u %s %c %u", 5u, "mid", 'x', 9u);
	printf(">\n");
	check(a, b);

	printf("--- %%u then %%%%\n");
	printf("std: <");
	a = printf("%u%%", 50u);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%u%%", 50u);
	printf(">\n");
	check(a, b);

	return (0);
}