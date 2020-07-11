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
	if (key.l == 0 && key.g == 0)
		ft_column_y(lst, key);
	else
		ft_key_l(lst, key);
	return (head);
}

static int ft_perm_check(t_req *fls)
{
	if (S_IRUSR & fls->mode && S_IXUSR & fls->mode)
		return (0);
	if (S_IRUSR & fls->mode)
		return (1);
	return (2);
}

int	ft_print_dir(t_req *lst, u_keys key)
{
	if (!key.R)
	{
		ft_putstr(lst->name);
		ft_putstr(":\n");
		return (1);
	}
	else
	{
		ft_putstr(lst->path);
		ft_putstr(":\n");
		return (1);
	}
}

t_req	*ft_distributer(t_req *lst, u_keys key, int stage)
{
	t_req	*tmp;
	int	flag;

	lst = handle_nodir(lst, key, stage);
	lst = ft_sorting(lst, key);
	tmp = lst;
	while(lst)
	{
		ft_print_dir(lst, key);
		flag = ft_perm_check(lst);
		if (!flag)
		{
			lst->right = ft_print_files(lst->right, key);
			ft_putchar('\n');
			if (key.R)
				lst->right = ft_distributer(lst->right, key, 1);
		}
		else if (flag == 2)
			ft_err(10, lst->name);
		lst = lst->next;
	}	
	return (tmp);
}
