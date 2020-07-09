#include "ft_ls.h"

t_req *ft_sorting(t_req *lst, u_keys key)
{
	if (key.f & 1)
		return (lst);
	if (lst)
	{
		lst = ft_lex_sort(lst);
		if (key.S & 1)
			lst = key_S_size(lst);
		if (key.t & 1)
			lst = key_t_time(lst);
		if (key.U & 1)
			lst = key_U_birth(lst);
		if (key.u & 1)
			lst = key_u_access(lst);
		if (key.r & 1)
			lst = key_r_reverse(lst);
	}
	return(lst);
}
/*
static void	ft_column_x(t_req *lst, u_keys key)
{
	while(lst)
	{
		if (key.i & 1)
			printf("%llu ", lst->inode);
		if (key.s & 1)
			printf("%lld ", lst->block);
		printf("%s", lst->name);
		if (key.k_1)
			printf("%s", "\n");
		else
			printf("%s", " ");
		lst = lst->next;
	}
	printf("%s", "\n");
}

void	ft_long_print(t_req *lst, u_keys key)
{
	while(lst)
	{
		if (key.i & 1)
			printf("%llu ", lst->inode);
		if (key.s & 1)
			printf("%lld ", lst->block);
		ft_ACL(lst->mode, lst->path);
		printf("   %d   ", lst->num_link);
		if (!key.g)
			printf(" %s    ", getpwuid(lst->own_uid)->pw_name);	
		printf(" %s    ", getgrgid(lst->grp_gid)->gr_name);
		printf("%lld", lst->size);
		printf(" %s\n", lst->name);
		lst = lst->next;
	}
}
*/
t_req	*ft_print_files(t_req *lst, u_keys key)
{
	int	sum;
	t_req	*head;

	lst = ft_sorting(lst, key);
	if(key.s || key.l)
		ft_summ_blocksize(lst);
	head = lst;
	if (key.l == 0&& key.g == 0)
		ft_column_y(lst, key);
	else
		ft_key_l(lst, key);
	return (head);
}

t_req	*ft_distributer(t_req *lst, u_keys key, int stage)
{
	t_req	*tmp;

	if (key.d)
	{
		lst = ft_sorting(lst, key);
		ft_print_files(lst, key);
		return (NULL);
	}
	lst = handle_nodir(lst, key, stage);
	lst = ft_sorting(lst, key);
	tmp = lst;
	while(lst)
	{
		if(key.R == 0)
			printf("%s:\n", lst->name);
		else
			printf("%s:\n", lst->path);
		lst->right = ft_print_files(lst->right, key);
		if (key.R)
			lst->right = ft_distributer(lst->right, key, 1);
		lst = lst->next;
	}	
	return (tmp);
}
