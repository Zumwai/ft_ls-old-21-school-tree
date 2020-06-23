#include "./includes/ft_ls.h"

int	main(int ac, char **av)
{
	u_keys	key;	
	t_req	files;

	if(ac > ARG_MAX)
		ft_err(2);
	if(ac == 1)
		ft_err(1);
	else
		key = ft_looker(av, ac);
	printf("%d\n", key.R);
	printf("%d\n", key.a);
	printf("%d\n", key.l);
	printf("%d\n", key.r);
	printf("%d\n", key.t);
	printf("%d\n", key.u);
	printf("%d\n", key.g);
	printf("%d\n", key.f);
	printf("%d\n", key.d);
	printf("%d\n", key.i);
	printf("%d\n", key.U);
	printf("%d\n", key.s);
	printf("%d\n", key.k_1);
	printf("%d\n", key.x);
	printf("%d\n", key.S);
	printf("%d\n", key.A);
	return (0);
}
