

#include "ft_printf.h"
#include <stdio.h>

typedef struct s_list
{
	void	*array[2];
	int		v1;
	char	v2;
}			t_list;

int	main(void)
{
	// int ftresult= ft_printf("hey dudde im ftprintf %");
	// printf("\n");
	// fflush(stdout);
	// int originalresult=printf("hey dudde im originalprintf %");
	// fflush(stdout);
	// ft_printf("\n");
	// ft_printf("\n");
	// ft_printf("ftresult : \noriginalresult: %d\n",originalresult);
	// int a = -1;
	// printf("%x",a);
	// printf("\n");
	// ft_printf("%x",a);
	// long h = 2147483648;
	// int res = printf("hey og %k %ld",h);
	// fflush(stdout);
	// printf("\n");
	// fflush(stdout);
	// int res2 = ft_printf("hey og %k %d",h);
	// fflush(stdout);
	// printf("\n%d\n%d", res, res2);
	// fflush(stdout);
	// printf("\n");
	// fflush(stdout);
	// return (0);


	t_list *t;

	t = malloc(sizeof(t_list));
	t->v1 = 42;
	t->v2 = 65;
	t->array[0] = &t->v1;
	t->array[1] = NULL;

	ft_printf("Result : %t", t);

	/* === OUTPUT ===
	Result : v1 = 42, adresse of v1 = Ox..., v2 = A, null = (nil);


}
/*
iv realised something, if i give it an unkown specifier like for example k:
	int res = printf("hey org_dudu uh %k");
	fflush(stdout);
	printf("\n");
	fflush(stdout);
	int res2 = ft_printf("hey ftp_dudu uh %k");
	printf("\n%d \n %d", res, res2);
it will print it normally:
	olgarh@c3r8p3 ~/f/learning> ./a.out | cat -e
	hey org_dudu uh %k$
	hey ftp_dudu uh %k$
	18 $
	18$
and if the character after % is '\0'
	int res = printf("hey org_dudu uh %");
	fflush(stdout);
	printf("\n");
	fflush(stdout);
	int res2 = ft_printf("hey ftp_dudu uh %");
	printf("\n%d \n %d", res, res2);
it will return -1
	olgarh@c3r8p3 ~/f/learning> ./a.out | cat -e
	hey org_dudu uh $
	hey ftp_dudu uh $
	-1 $
	-1$
so all good so far, now lets try something,
	if instead of '\0' we just added a space,
	int res = printf("hey org_dudu uh % ");
	fflush(stdout);
	printf("\n");
	fflush(stdout);
	int res2 = ft_printf("hey ftp_dudu uh % ");
	printf("\n%d \n %d", res, res2);
we get in the original  -1
	olgarh@c3r8p3 ~/f/learning> ./a.out | cat -e
	hey org_dudu uh $
	hey ftp_dudu uh % $
	-1 $
	18$
but if we write before it a %k like:
	int res = printf("hey org_dudu uh %k % ");
	fflush(stdout);
	printf("\n");
	fflush(stdout);
	int res2 = ft_printf("hey ftp_dudu uh %K % ");
	printf("\n%d \n %d", res, res2);
we get:
	olgarh@c3r8p3 ~/f/learning> ./a.out | cat -e
	hey org_dudu uh %k % $
	hey ftp_dudu uh %K % $
	21 $
	21$
which is pretty strange, does the rule of when we have ' ' after
	% changes if we print
	%k or any specifier before it either if its valid or no
its pretty weird

*/
// so like this:
// 	int res = printf("hey org_dudu uh %k %\0 wow this is weird");
// 	fflush(stdout);
// 	printf("\n");
// 	fflush(stdout);
// 	int res2 = ft_printf("hey ftp_dudu uh %k %\0 wow this is weird");
// 	printf("\n%d\n%d", res, res2);
// 	fflush(stdout);
// i get:
//     olgarh@c3r8p3 ~/f/learning> ./a.out | cat -e
//     hey org_dudu uh %k %$
//     hey ftp_dudu uh %k $
//     20$
//     -1$
