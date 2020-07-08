#include "ft_ls.h"

static	t_req *ft_sorting(t_req *lst, u_keys key)
{
	if (lst)
	{
		lst = ft_lex_sort(lst);
		if (key.S)
			lst = key_S_size(lst);
		if (key.t)
			lst = key_t_time(lst);
		if (key.U)
			lst = key_U_birth(lst);
		if (key.u)
			lst = key_u_access(lst);
		if (key.r)
			lst = key_r_reverse(lst);
	}
	return(lst);
}

void	ft_print_files(t_req *lst, u_keys key)
{
	t_req	*tmp;
	
	tmp = lst;
	tmp = ft_sorting(tmp, key);
	while(tmp)
	{
		printf("%s ", tmp->name);
		tmp = tmp->next;
	}
}

int	ft_distributer(t_req *lst, u_keys key, int stage)
{
	t_req	*tmp;
//	if (!stage)
	lst = handle_nodir(lst, key, stage);
	lst = ft_sorting(lst, key);
	while(lst)
	{
		printf("%s:\n", lst->name);
		tmp = lst->right;
		ft_print_files(tmp, key);
		puts("");
		if (key.R)
		{
			puts("i am segfault");
			ft_distributer(lst->right, key, 1);
		}
		puts("");
		lst = lst->next;
	}
	return (0);
}
