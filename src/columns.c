/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   columns.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 13:34:57 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 12:46:31 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_find_max(t_req *fls, int key, int len[5])
{
	while (fls)
	{
		if (key & K_I)
			len[1] = MAX(len_num(fls->inode) + 1, len[1]);
		if (key & K_S)
			len[2] = MAX(len_num(fls->block) + 1, len[2]);
		len[3] = MAX(ft_strlen(fls->name), len[3]);
		len[4]++;
		fls = fls->next;
	}
	len[0] = len[1] + len[2] + len[3] + 2;
}

static void	ft_show_name(t_req *fls, int key, int max[4], int col)
{
	int		len_s;
	int		len_i;
	int		check;

	len_s = 0;
	len_i = 0;
	if (key & K_I)
		len_i = ft_is_key(fls->inode, max[1]);
	if (key & K_S)
		len_s = ft_is_key(fls->block, max[2]);
	ft_putstr(fls->name);
	check = MAX((max[0] - ft_strlen(fls->name) - len_s - len_i), 0);
	if (col)
		while (check--)
			ft_putchar(' ');
}

static void	ft_print_y_col(t_req *fls, int key, int max[4], int coor[2])
{
	int		col;
	int		row;
	t_req	*tmp;
	int		all_row;

	all_row = coor[1];
	while (fls && all_row--)
	{
		col = coor[0];
		tmp = fls->next;
		while (fls && col--)
		{
			ft_show_name(fls, key, max, col);
			row = coor[1];
			while (fls && row--)
				fls = fls->next;
		}
		ft_putchar('\n');
		fls = tmp;
	}
}

static void	ft_print_x_col(t_req *fls, int key, int max[4], int coor[2])
{
	int	col;
	int	all_col;

	all_col = coor[1];
	while (fls && all_col--)
	{
		col = coor[0];
		while (fls && col--)
		{
			ft_show_name(fls, key, max, col);
			fls = fls->next;
		}
		ft_putchar('\n');
	}
}

void		ft_column_y(t_req *fls, int key)
{
	struct winsize	win;
	int				max[5];
	int				coor[2];

	if (!fls)
		return ;
	ioctl(0, TIOCGWINSZ, &win);
	ft_zero(max, 5);
	ft_find_max(fls, key, max);
	if (max[0] < win.ws_col)
		coor[0] = (win.ws_col / max[0]);
	else
		coor[0] = 1;
	coor[1] = max[4];
	if (!(key & K_1))
		coor[1] = coor[1] / coor[0] + 1;
	if (!(key & K_X))
		ft_print_y_col(fls, key, max, coor);
	else
		ft_print_x_col(fls, key, max, coor);
}
