
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

	printf("--- c1: single char\n");
	printf("std: <");
	a = printf("%c", 'a');
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%c", 'a');
	printf(">\n");
	check(a, b);

	printf("--- c2: space\n");
	printf("std: <");
	a = printf("%c", ' ');
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%c", ' ');
	printf(">\n");
	check(a, b);

	printf("--- c3: newline char\n");
	printf("std: <");
	a = printf("%c", '\n');
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%c", '\n');
	printf(">\n");
	check(a, b);

	printf("--- c4: NUL char (counts as 1)\n");
	printf("std: <");
	a = printf("%c", 0);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%c", 0);
	printf(">\n");
	check(a, b);

	printf("--- c5: two %%c back to back\n");
	printf("std: <");
	a = printf("%c%c", 'o', 'k');
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%c%c", 'o', 'k');
	printf(">\n");
	check(a, b);

	printf("--- c6: %%c in the middle of text\n");
	printf("std: <");
	a = printf("a%cb", '-');
	printf(">\n");
	printf("ft : <");
	b = ft_printf("a%cb", '-');
	printf(">\n");
	check(a, b);

	printf("--- c7: %%c mixed with %%s\n");
	printf("std: <");
	a = printf("%c %s %c", 'x', "mid", 'y');
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%c %s %c", 'x', "mid", 'y');
	printf(">\n");
	check(a, b);

	printf("--- c8: %%c then %%%%\n");
	printf("std: <");
	a = printf("%c%%", 'z');
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%c%%", 'z');
	printf(">\n");
	check(a, b);

	printf("--- c9: char given as a number (65 = A)\n");
	printf("std: <");
	a = printf("%c", 65);
	printf(">\n");
	printf("ft : <");
	b = ft_printf("%c", 65);
	printf(">\n");
	check(a, b);

	return (0);
}
