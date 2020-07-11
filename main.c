#include "./includes/ft_ls.h"

int	main(int ac, char **av)
{
	u_keys	key;	
	t_req	*files;
	int	i;

	i = 0;
	files = NULL;
	if(ac > ARG_MAX)
		ft_err(2, "ARG_MAX");
	key = ft_looker(av, ac, &i);
	files = fill_list(&av[i], ac - i);	
	ft_parse_av(files, key, ac - i, 2);
	/*
	if (key.d)
	{
		files = ft_sorting(files, key);
		ft_print_files(files, key);
		return (0);
	}
	*/
	ft_distributer(files, key, 0);
	return (0);
}
