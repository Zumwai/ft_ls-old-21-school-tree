#include "ft_ls.h"

int	ft_find_max(t_req *fls, u_keys key)
{
	int	len;
	int	tmp;

	len = 0;
	while(fls)
	{
		tmp = 0;
		if (key.i)
			tmp += len_num(fls->inode) + 1;
		if (key.s)
			tmp += len_num(fls->block) + 1;
		tmp += ft_strlen(fls->name);
		len = max(tmp, len);
		fls = fls->next;
	}
	return (len);
}

void	ft_naming(t_req *fls, int s, int i, int max)
{
	int	tmp;
	
	tmp = 0;
	if (i)
		tmp += len_num(fls->inode) + 1;
	if (s)
		tmp += len_num(fls->block) + 1;
	tmp += ft_strlen(fls->name);
	while (


void	ft_print_y_col(t_req *fls, u_keys key, int max, struct winsize win)
{
	int	tmp_col;
	int	tmp_row;
	t_req	*tmp_lst;
	
	while (fls)
	{
		tmp_col = win.ws_col;
		tmp_lst = fls->next;
		while (fls && tmp_col--)
		{
			ft_naming(fls, key.s, key.i, max);

		}
	}
}

void	ft_column_y(t_req *fls, u_keys key)
{
	int		max[3];
	struct winsize	win;
	t_req		*tmp;


	ioctl(0, TIOCGWINSZ, &win);
	max[0] = ft_find_max(fls, key);
	max[1] = win.ws_col / max[0];
	tmp = fls;
	max[2] = 0;
	while(tmp)
	{
		max[2] += 1;
		tmp = tmp->next;
	}
	max[2] = max[2] / max[0];
}
