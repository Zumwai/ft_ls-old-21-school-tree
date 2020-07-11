#include "ft_ls.h"

void	ft_find_max(t_req *fls, u_keys key, int len[4])
{
	int	tmp;

	while(fls)
	{
		tmp = 0;
		if (key.i)
		{
			tmp = len_num(fls->inode) + 1;
			len[1] = MAX(tmp, len[1]);
		}
		if (key.s)
		{
			tmp = len_num(fls->block) + 1;
			len[2] = MAX(tmp, len[2]);
		}
		tmp = ft_strlen(fls->name);
		len[3] = MAX(tmp, len[3]);
		fls = fls->next;
	}
	len[0] = len[1] + len[2] + len[3] + 3;
}

void	ft_show_name(t_req *fls, u_keys key, int max[4], int col)
{
	int	len_s;
	int	len_i;
	int	check;

	len_s = 0;
	len_i = 0;
	if (key.i != 0)
	{
		len_i = len_num(fls->inode);
		while(max[1] > len_i++)
			ft_putchar(' ');
		ft_putnbr(fls->inode);
		ft_putchar(' ');
	}
	if (key.s != 0)
	{
		len_s = len_num(fls->block);
		while(max[2] > len_s++)
			ft_putchar(' ');
		ft_putnbr(fls->block);
		ft_putchar(' ');
	}	
	ft_putstr(fls->name);
	check = MAX((max[0] - ft_strlen(fls->name) - len_s - len_i), 0);
	if (col)
		while(check--)
			ft_putchar(' ');
	
}
	

void	ft_print_y_col(t_req *fls, u_keys key, int max[4], int coor[2])
{
	int	col;
	int	row;
	t_req	*tmp;
	int	all_row;

	all_row = coor[1];
	while(fls && all_row--)
	{
		col = coor[0];
		tmp = fls->next;
		while (fls && col--)
		{
			ft_show_name(fls, key, max, col);
			row = coor[1];
			while(fls && row--)
				fls = fls->next;
		}
		ft_putchar ('\n');
		fls = tmp;
	}
}

void	ft_print_x_col(t_req *fls, u_keys key, int max[4], int coor[2])
{
	int	col;
	int	row;
	int	all_col;
	t_req	*tmp;

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

void	ft_column_y(t_req *fls, u_keys key)
{
	int		max[4];
	int		coor[2];
	struct winsize	win;
	t_req		*tmp;

	if (!fls)
		return ;
	ioctl(0, TIOCGWINSZ, &win);
	max[0] = 0;
	max[1] = 0;
	max[2] = 0;
	max[3] = 0;
	ft_find_max(fls, key, max);
//	printf("\n%d - max[0], %d - max[1], %d - max[2], %d - max[3]\n", max[0], max[1], max[2], max[3]);
	if (max[0])
		coor[0] = win.ws_col / max[0];
	else
		coor[0] = 0;
	tmp = fls;
	coor[1] = 0;
	while(tmp)
	{
		coor[1] += 1;
		tmp = tmp->next;
	}
	if (!key.k_1)
		coor[1] = (coor[1] % coor[0] ? 1 : 0) + coor[1] / coor[0];
	printf("\n%d - maxlen[0], %d - coor [0], %d - coor[1]\n", max[0], coor[0], coor[1]);
	if (!key.x)
		ft_print_y_col(fls, key, max, coor);
	else
		ft_print_x_col(fls, key, max, coor);
}
