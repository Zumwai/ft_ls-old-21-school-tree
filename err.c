#include "./includes/ft_ls.h"

void	ft_err(int i, char *av)
{
	printf("%d\n", i);
	if (i != 4 && i != 3)
	{
		ft_putstr_fd("./ft_ls: ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr(": ");
	}
//	perror("./ft_ls: ");
	if (i != 7 && i != 4 && i != 3)
		ft_putstr_fd(strerror(errno), 2);
	if (i == 4 || i == 3)
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putstr_fd(av, 2);
		ft_putstr_fd("\nusage: ft_ls [", 2);
		ft_putstr_fd(OPTIONS, 2);
		ft_putstr_fd("] ", 2);
		ft_putstr_fd("[file ...]\n", 2);
	}
	if (i != 5)
		exit(-1);
}
