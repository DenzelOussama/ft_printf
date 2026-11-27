#include "ft_printf.h"

void	check(int a, int b)
{
	if (a == b)
		printf("OK\n\n");
	else
		printf("KO (std=%d, ft=%d)\n\n", a, b);
}

int	main(void)
{
	int a;
	int b;
	char *n = NULL;
	char *big = "Lorem ipsum dolor sit amet, consectetur adipiscing elit";

	setvbuf(stdout, NULL, _IONBF, 0);

	printf("--- test 1: no specifier\n");
	printf("std: <");
	a = printf("no specifier");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("no specifier");
	printf(">\n");
	check(a, b);

	printf("--- test 2: empty format\n");
	printf("std: <");
	a = printf("");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("");
	printf(">\n");
	check(a, b);

	printf("--- test 3: %%s hello\n");
	printf("std: <");
	a = printf("%s", "hello");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%s", "hello");
	printf(">\n");
	check(a, b);

	printf("--- test 4: %%s empty string\n");
	printf("std: <");
	a = printf("%s", "");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%s", "");
	printf(">\n");
	check(a, b);

	printf("--- test 5: %%s NULL\n");
	printf("std: <");
	a = printf("[%s]", n);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("[%s]", n);
	printf(">\n");
	check(a, b);

	printf("--- test 6: two %%s back to back\n");
	printf("std: <");
	a = printf("%s%s", "ab", "cd");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%s%s", "ab", "cd");
	printf(">\n");
	check(a, b);

	printf("--- test 7: three %%s with spaces\n");
	printf("std: <");
	a = printf("%s %s %s", "a", "b", "c");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%s %s %s", "a", "b", "c");
	printf(">\n");
	check(a, b);

	printf("--- test 8: %%s then text at the end\n");
	printf("std: <");
	a = printf("%s!!", "x");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%s!!", "x");
	printf(">\n");
	check(a, b);

	printf("--- test 9: %%s at the end\n");
	printf("std: <");
	a = printf("start %s", "x");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("start %s", "x");
	printf(">\n");
	check(a, b);

	printf("--- test 10: %%s at the start\n");
	printf("std: <");
	a = printf("%s end", "x");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%s end", "x");
	printf(">\n");
	check(a, b);

	printf("--- test 11: %%%% alone\n");
	printf("std: <");
	a = printf("%%");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%%");
	printf(">\n");
	check(a, b);

	printf("--- test 12: %%s then %%%%\n");
	printf("std: <");
	a = printf("%s%%", "x");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%s%%", "x");
	printf(">\n");
	check(a, b);

	printf("--- test 13: %%%% then %%s\n");
	printf("std: <");
	a = printf("100%% %s", "sure");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("100%% %s", "sure");
	printf(">\n");
	check(a, b);

	printf("--- test 14: newline inside the string\n");
	printf("std: <");
	a = printf("%s", "multi\nline");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%s", "multi\nline");
	printf(">\n");
	check(a, b);

	printf("--- test 15: tabs\n");
	printf("std: <");
	a = printf("tab\t%s\t|", "x");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("tab\t%s\t|", "x");
	printf(">\n");
	check(a, b);

	printf("--- test 16: long string\n");
	printf("std: <");
	a = printf("%s", big);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%s", big);
	printf(">\n");
	check(a, b);

	printf("--- test 17: long string then text\n");
	printf("std: <");
	a = printf("%s %s", big, "after");
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%s %s", big, "after");
	printf(">\n");
	check(a, b);

	return (0);
}
