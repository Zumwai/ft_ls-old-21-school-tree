#include "./includes/ft_ls.h"

int	main(int ac, char **av)
{
	u_keys	key;	
	t_req	*files;
	int	i;

	i = 0;
	files = NULL;
	if(ac > ARG_MAX)
		ft_err(2);
	key = ft_looker(av, ac, &i);
	files = fill_list(&av[i], ac - i);	
	ft_parse_av(files, key, ac - i, 2);
	files = handle_nodir(files, key);
/*
	printf("key R %d\n", key.R);
	printf("key a %d\n", key.a);
	printf("key l %d\n", key.l);
	printf("key r %d\n", key.r);
	printf("key t %d\n", key.t);
	printf("key u %d\n", key.u);
	printf("key g %d\n", key.g);
	printf("key f %d\n", key.f);
	printf("key d %d\n", key.d);
	printf("key i %d\n", key.i);
	printf("key U %d\n", key.U);
	printf("key s %d\n", key.s);
	printf("key 1 %d\n", key.k_1);
	printf("key x %d\n", key.x);
	printf("key S %d\n", key.S);
	printf("key A %d\n", key.A);
	printf("WE GOT HIM ITS A NAME %s\n", files->name);
	printf("WE GOT HIS ADRESS %s\n", files->path);
	while(files)
	{
		printf("%s name\n%s path\n-------\n", files->name, files->path);
		files = files->next;
		}
		*/
	return (0);
}
