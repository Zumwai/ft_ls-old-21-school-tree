#include "./includes/ft_ls.h"

void	ft_err(int i, char *av)
{
	if (i != 4 && i != 3)
	{
		ft_putstr_fd("ft_ls: ", 2);
		if (i != 10)
			ft_putstr_fd(av, 2);
		ft_putstr(": ");
	}
//	perror("./ft_ls: ");
	if (i != 7 && i != 4 && i != 3)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar('\n');
	}
	if (i == 4 || i == 3)
	{
		ft_putstr_fd("ft_ls: illegal option -- -", 2);
	//	ft_putstr_fd(av, 2);
		ft_putstr_fd("\nusage: ft_ls [-", 2);
		ft_putstr_fd(OPTIONS, 2);
		ft_putstr_fd("] ", 2);
		ft_putstr_fd("[file ...]\n", 2);
	}
	if (i != 5 && i != 10)
		exit(-1);
}
