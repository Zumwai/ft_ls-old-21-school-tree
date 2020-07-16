/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_t_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 14:59:15 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 14:52:14 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	t_req	*ft_shift_time(t_req *fls)
{
	t_req	*r;
	t_req	*l;
	t_req	*head;

	l = fls;
	r = fls->next;
	head = r;
	while (r != NULL && fls->mtime < r->mtime)
	{
		l = r;
		r = r->next;
	}
	l->next = fls;
	fls->next = r;
	return (head);
}

t_req			*key_t_time(t_req *fls)
{
	if (!fls)
		return (NULL);
	fls->next = key_t_time(fls->next);
	if (fls->next != NULL && fls->mtime < fls->next->mtime)
		fls = ft_shift_time(fls);
	return (fls);
}

int				ft_is_key(int inos, int max)
{
	int	len;

	len = len_num(inos);
	while (max - 1 > len++)
		ft_putchar(' ');
	ft_putnbr(inos);
	ft_putchar(' ');
	return (len);
}

void			ft_put_link(char path[PATH_MAX])
{
	char	buf[NAME_MAX];
	int		red;

	ft_bzero(buf, NAME_MAX);
	if ((red = readlink(path, buf, NAME_MAX) > 0))
	{
		ft_putstr(" -> ");
		ft_putstr(buf);
	}
}
