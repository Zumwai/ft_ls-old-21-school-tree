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
	exit(1);
}
