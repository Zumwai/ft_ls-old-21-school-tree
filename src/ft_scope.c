/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 13:34:57 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 13:24:42 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_req		*ft_sorting(t_req *lst, int key)
{
	if (key & K_F)
		return (lst);
	if (lst)
	{
		lst = ft_lex_sort(lst);
		if (key & K_SS)
			lst = key_big_size(lst);
		if (key & K_T)
		{
			if (key & K_UU)
				lst = key_birth(lst);
			if (key & K_U)
				lst = key_u_access(lst);
			if (!(key & K_U) && !(key & K_UU))
				lst = key_t_time(lst);
		}
		if (key & K_R)
			lst = key_r_reverse(lst);
	}
	return (lst);
}

t_req		*ft_print_files(t_req *lst, int key)
{
	t_req	*head;

	if (!lst)
		return (lst);
	lst = ft_sorting(lst, key);
	if ((key & K_S) || (key & K_L))
		ft_summ_blocksize(lst);
	head = lst;
	if ((key & K_L) || (key & K_G))
		ft_key_l(lst, key);
	else
		ft_column_y(lst, key);
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

static int	ft_print_dir(t_req *lst, int key, int stage)
{
	if (stage == 1)
		ft_putchar('\n');
	if (!(key & K_RR))
		ft_putstr(lst->name);
	else
		ft_putstr(lst->path);
	ft_putstr(":\n");
	stage = 2;
	return (1);
}

t_req		*ft_distributer(t_req *lst, int key, int stage)
{
	t_req	*tmp;
	int		flag;

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
			if (key & K_RR)
				lst->right = ft_distributer(lst->right, key, 1);
		}
		else if (flag == 2)
			ft_err(10, lst->name);
		stage = 1;
		lst = lst->next;
	}
	return (tmp);
}
