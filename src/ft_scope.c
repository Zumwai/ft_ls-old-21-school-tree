/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 13:34:57 by aophion           #+#    #+#             */
/*   Updated: 2020/07/15 13:28:25 by aophion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_req		*ft_sorting(t_req *lst, u_keys key)
{
	if (key.f & 1)
		return (lst);
	if (lst)
	{
		lst = ft_lex_sort(lst);
		if (key.S & 1)
			lst = key_S_size(lst);
		if (key.t & 1)
		{
			if (key.U & 1)
				lst = key_U_birth(lst);
			if (key.u & 1)
				lst = key_u_access(lst);
			if (key.u == 0 && key.U == 0)
				lst = key_t_time(lst);
		}
		if (key.r & 1)
			lst = key_r_reverse(lst);
	}
	return(lst);
}

t_req		*ft_print_files(t_req *lst, u_keys key)
{
	t_req	*head;

	if (!lst)
		return (lst);
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

static int	ft_perm_check(t_req *fls)
{
	if (S_IRUSR & fls->mode && S_IXUSR & fls->mode)
		return (0);
	if (S_IRUSR & fls->mode)
		return (1);
	return (2);
}

static int	ft_print_dir(t_req *lst, u_keys key, int stage)
{
	if (stage == 1)
		ft_putchar('\n');
	if (!key.R)
		ft_putstr(lst->name);
	else
		ft_putstr(lst->path);
	ft_putstr(":\n");
	stage = 2;
	return (1);
}

t_req		*ft_distributer(t_req *lst, u_keys key, int stage)
{
	t_req	*tmp;
	int	flag;

	lst = handle_nodir(lst, key, &stage);
	lst = ft_sorting(lst, key);
	tmp = lst;
	while (lst)
	{
		if (stage == 1 || stage == 4 || lst->next)
			ft_print_dir(lst, key, stage);
		flag = ft_perm_check(lst);
		if (!flag)
		{
			lst->right = ft_print_files(lst->right, key);
			if (key.R)
				lst->right = ft_distributer(lst->right, key, 1);
		}
		else if (flag == 2)
			ft_err(10, lst->name);
		stage = 1;
		lst = lst->next;
	}	
	return (tmp);
}
