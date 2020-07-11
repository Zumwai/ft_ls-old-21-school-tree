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
	if (key.i == 0)
	{
		len_i = len_num(fls->inode);
		while(max[1] > len_i++)
			ft_putchar(' ');
		ft_putnbr(fls->inode);
		ft_putchar(' ');
	}
	if (key.s == 0)
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
	int	tmp_col;
	int	tmp_row;
	t_req	*tmp_lst;
	int	count;

//	puts("been there 0 ");
	count = coor[1];
//	printf("%d - coor[0], %d - coor[1]\n", coor[0], coor[1]);
	while(fls && count--)
	{
//		puts("been there 1");
		tmp_col = coor[0];
		tmp_lst = fls->next;
		while (fls && tmp_col--)
		{
			ft_show_name(fls, key, max, tmp_col);
	//		puts("been there 2");
			tmp_row = coor[1];
			while(fls && tmp_row--)
				fls = fls->next;
		//	ft_putstr("  ");
		}
		ft_putchar ('\n');
		fls = tmp_lst;;
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
	coor[0] = win.ws_col / max[0];
	tmp = fls;
	coor[1] = 0;
	while(tmp)
	{
		coor[1] += 1;
		tmp = tmp->next;
	}
	if (!key.k_1)
		coor[1] = (coor[1] % coor[0] ? 1 : 0) + coor[1] / coor[0];
//	printf("\n%d - maxlen[0], %d - coor [0], %d - coor[1]\n", max[0], coor[0], coor[1]);
	ft_print_y_col(fls, key, max, coor);
}
