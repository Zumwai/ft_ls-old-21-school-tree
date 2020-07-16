/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 13:51:33 by student           #+#    #+#             */
/*   Updated: 2020/07/16 14:54:55 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_calc_uid(t_req *fls, int max)
{
	struct passwd	*uid;
	int				ret;

	ret = 0;
	uid = NULL;
	if ((uid = getpwuid(fls->own_uid)) != NULL)
		ret = MAX(ft_strlen(uid->pw_name), max);
	else
		ret = MAX(len_num(fls->own_uid), max);
	return (ret);
}

int		ft_calc_gid(t_req *fls, int max)
{
	struct group	*gid;
	int				ret;

	ret = 0;
	gid = NULL;
	if ((gid = getgrgid(fls->grp_gid)) != NULL)
		ret = MAX(ft_strlen(gid->gr_name), max);
	else
		ret = MAX(len_num(fls->grp_gid), max);
	return (ret);
}

void	ft_special(t_req *fls, int size[8])
{
	int		len;

	if (S_ISCHR(fls->mode))
	{
		len = len_num(major(fls->req_dev));
		while (size[6] > len++)
			ft_putchar(' ');
		ft_putnbr(major(fls->req_dev));
		ft_putstr(", ");
		len = len_num(minor(fls->req_dev));
		while (size[7] > len++)
			ft_putchar(' ');
		ft_putnbr(minor(fls->req_dev));
		ft_putchar(' ');
	}
	else
	{
		len = len_num(fls->size) - 1;
		while (size[5] > len++)
			ft_putchar(' ');
		ft_putnbr(fls->size);
		ft_putchar(' ');
	}
}

int		ft_check_link(t_req *lst, char a)
{
	char	buf[NAME_MAX];
	int		red;

	if (a != 'l')
		return (2);
	if (a == 'l')
	{
		ft_bzero(buf, NAME_MAX);
		if ((red = readlink(lst->path, buf, NAME_MAX) == -1))
		{
			ft_putchar('\n');
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(lst->path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (1);
		}
	}
	return (0);
}
