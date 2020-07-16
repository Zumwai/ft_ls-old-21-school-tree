/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 11:56:22 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 15:24:15 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_calc_padding(t_req *fls, int size[8], int key)
{
	while (fls)
	{
		if (key & K_I)
			size[0] = MAX(len_num(fls->inode), size[0]);
		if (key & K_S)
			size[1] = MAX(len_num(fls->block), size[1]);
		size[2] = MAX(len_num(fls->num_link), size[2]);
		size[3] = ft_calc_uid(fls, size[3]);
		size[4] = ft_calc_gid(fls, size[4]);
		if (S_ISCHR(fls->mode))
		{
			size[6] = MAX(len_num(major(fls->req_dev)), size[6]);
			size[7] = MAX(len_num(minor(fls->req_dev)), size[7]);
		}
		else
			size[5] = MAX(len_num(fls->size), size[5]);
		fls = fls->next;
	}
	return (0);
}

static void	ft_printer(t_req *fls, int size[8], int key, char p[11])
{
	int	len;

	ft_putstr(p);
	ft_putchar(' ');
	len = len_num(fls->num_link);
	while (size[2] + 1 > len++)
		ft_putchar(' ');
	ft_putnbr(fls->num_link);
	ft_putchar(' ');
	if (!(key & K_G))
	{
		ft_pw_uid(getpwuid(fls->own_uid), size[3], fls->own_uid);
		ft_putstr("  ");
	}
	ft_gr_gid(getgrgid(fls->grp_gid), size[4], fls->grp_gid);
	ft_putchar(' ');
	ft_special(fls, size);
}

void		print_key_is(t_req *fls, int size[8], int key)
{
	int	len;

	if (key & K_I)
	{
		len = len_num(fls->inode);
		while (size[0] > len++)
			ft_putchar(' ');
		ft_putnbr(fls->inode);
		ft_putchar(' ');
	}
	if (key & K_S)
	{
		len = len_num(fls->block);
		while (size[1] > len++)
			ft_putchar(' ');
		ft_putnbr(fls->block);
		ft_putchar(' ');
	}
}

void		print_time(char *str, long long clock)
{
	long long	tmp;
	time_t		curr;
	int			i;

	curr = time(&curr);
	tmp = curr - clock;
	if (ABS(tmp) > 15768000)
	{
		i = 4;
		while (i < 10)
			ft_putchar(str[i++]);
		i = 19;
		ft_putchar(' ');
		while (i < 24)
			ft_putchar(str[i++]);
	}
	else
	{
		i = 4;
		while (i < 16)
			ft_putchar(str[i++]);
	}
}

void		ft_key_l(t_req *lst, int key)
{
	char	perm[11];
	int		size[8];
	int		link;

	ft_zero(size, 8);
	ft_bzero(perm, 11);
	ft_calc_padding(lst, size, key);
	while (lst)
	{
		if ((key & K_I) || (key & K_S))
			print_key_is(lst, size, key);
		ft_mode(lst->mode, perm);
		link = ft_check_link(lst, perm[0]);
		ft_printer(lst, size, key, perm);
		print_time(ctime(&lst->mtime), lst->mtime);
		ft_putchar(' ');
		ft_putstr(lst->name);
		if (!link)
			ft_put_link(lst->path);
		ft_putchar('\n');
		lst = lst->next;
	}
}
