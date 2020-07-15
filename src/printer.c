/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 11:56:22 by aophion           #+#    #+#             */
/*   Updated: 2020/07/12 12:12:22 by aophion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_calc_padding(t_req *fls, int size[6], u_keys key)
{
	struct passwd	*uid;
	struct group	*gid;

	while (fls)
	{
		if (key.i)		
			size[0] = MAX(len_num(fls->inode), size[0]);
		if (key.s)
			size[1] = MAX(len_num(fls->block), size[1]);
		size[2] = MAX(len_num(fls->num_link), size[2]);
		if ((uid = getpwuid(fls->own_uid)) != NULL)
			size[3] = MAX(ft_strlen(getpwuid(fls->own_uid)->pw_name), size[3]);
		else
			size[3] = MAX(len_num(fls->own_uid), size[3]);
		if ((gid = getgrgid(fls->grp_gid)) != NULL)
			size[4] = MAX(ft_strlen(gid->gr_name), size[4]);
		else
			size[4] = MAX(len_num(fls->grp_gid), size[4]);
		size[5] = MAX(len_num(fls->size), size[5]);
		fls = fls->next;
	}
	return (0);
}



static void	ft_printer(t_req *fls, int size[6], int g)
{
	int	len;
	len = len_num(fls->num_link);
	while (size[2] + 1> len++)
		ft_putchar(' ');
	ft_putnbr(fls->num_link);
	ft_putchar(' ');
	if (!g)
	{
		ft_pw_uid(getpwuid(fls->own_uid), size[3], fls->own_uid);
		ft_putstr("  ");
	}
	ft_gr_gid(getgrgid(fls->grp_gid), size[4], fls->grp_gid);
	ft_putchar (' ');
	len = len_num(fls->size) - 1;
	while (size[5] > len++)
		ft_putchar (' ');
	ft_putnbr(fls->size);
	ft_putchar (' ');
}

void	print_key_is(t_req *fls, int size[6], int i, int s)
{
	int	len;

	if (i)
	{
		len = len_num(fls->inode);
		while (size[0] > len++)
			ft_putchar(' ');
		ft_putnbr(fls->inode);
		ft_putchar(' ');
	}
	if (s)
	{
		len = len_num(fls->block);
		while (size[1] > len++)
			ft_putchar(' ');
		ft_putnbr(fls->block);
		ft_putchar(' ');
	}
}

void	print_time(char *str, long long clock)
{
	int i;
	time_t	curr;
	long long	tmp;

	curr = time(&curr);
	tmp = curr - clock;
	if (ABS(tmp) > 15768000)
	{
		i = 4;
		while(i < 10)
			write(1, &str[i++], 1);
		i = 19;
		ft_putchar(' ');
		while(i < 24)
			write(1, &str[i++], 1);
	}
	else
	{
		i = 4;
		while(i < 16)
			write(1, &str[i++], 1);
	}
}
		
void	ft_key_l(t_req *lst, u_keys key)
{
	int	size[6];
	char	perm[11];

	ft_zero(size, 6);
	ft_bzero(perm, 11);
	ft_calc_padding(lst, size, key);
	while (lst)
	{
		if (key.i || key.s)
			print_key_is(lst, size, key.i, key.s);
		ft_ACL(lst->mode, perm);
		ft_putchar(' ');
		ft_printer(lst, size, key.g);
		print_time(ctime(&lst->mtime), lst->mtime);
		ft_putchar(' ');
		ft_putstr(lst->name);
		if (perm[0] == 'l')
			ft_put_link(lst->path);
		ft_putchar('\n');
		lst = lst->next;
	}
}
