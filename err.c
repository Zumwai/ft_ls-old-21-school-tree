#include "./includes/ft_ls.h"

void	ft_err(int i)
{
	if (i == 1)
		printf("%s\n", "ft_ls usage: no arguments\nexit code 1");
	if (i == 2)
		printf("%s\n", "ft_ls usage: argument list too long\nexit code 2");
	if (i == 3)
		printf("%s\n", "ft_ls usage: no such key\nexit code 3");
	if (i == 4)
		printf("%s\n", "ft_ls usage: unrecognized option\nexit code 4");
	if (i == 5)
		printf("%s\n", "ft_ls NAME IS WRONG\nexit code 5");
	if (i == 6)
		printf("%s\n", "ft_ls malloc failure at new entry\nexit code 6");
	if (i == 7)
		printf("%s\n", "ft_ls path too long\nexit code 7");
	exit(-1);
}
