#include "ft_ls.h"

void	ft_column_y(t_req *lst, u_keys key)
{
	while(lst)
	{
		if (key.i & 1)
			printf("%llu ", lst->inode);
		if (key.s & 1)
			printf("%llu ", lst->block);
		printf("%s", lst->name);
		if (key.k_1)
			printf("%s", "\n");
		else
			printf("%s", " ");
			lst = lst->next;
	}
	ft_putchar('\n');
}

int	len_num(int n)
{
	int	len;

	len = 1;
	while (n / 10)
	{
		n /= 10;
		++len;
	}
	return (len);
}

static int	ft_calc_padding(t_req *fls, int size[6], u_keys key)
{
	int	len;

	while (fls)
	{
		if (key.i)		
			size[0] = MAX(len_num(fls->inode), size[0]);
		if (key.s)
			size[1] = MAX(len_num(fls->block), size[1]);
		size[2] = MAX(len_num(fls->num_link), size[2]);
		size[3] = MAX(ft_strlen(getpwuid(fls->own_uid)->pw_name), size[3]);		//LIB FUNC
		size[4] = MAX(ft_strlen(getgrgid(fls->grp_gid)->gr_name), size[4]);		//LIB FUNC
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
		len = ft_strlen(getpwuid(fls->own_uid)->pw_name);
		while (size[3] > len++)
			ft_putchar(' ');
		ft_putstr(getpwuid(fls->own_uid)->pw_name);
		ft_putchar(' ');
	}
	len = ft_strlen(getgrgid(fls->grp_gid)->gr_name);
	while (size[4] > len++)
		ft_putchar(' ');
	ft_putstr(getgrgid(fls->grp_gid)->gr_name);
	ft_putchar (' ');
	len = len_num(fls->size);
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

void	print_time(char *str)
{
	int i;
	time_t	curr;



	i = 4;
	while(i < 16)
		write(1, &str[i++], 1);
}
		
void	ft_key_l(t_req *lst, u_keys key)
{
	int	size[6];
	char	perm[11];
	char	buf[NAME_MAX];
	char	*teatime;

	size[0] = 0;
	size[1] = 0;
	size[2] = 0;	
	size[3] = 0;
	size[4] = 0;
	size[5] = 0;
	ft_bzero(perm, 11);
	ft_calc_padding(lst, size, key);
	while (lst)
	{
		if (key.i || key.s)
			print_key_is(lst, size, key.i, key.s);
		ft_ACL(lst->mode, lst->path, perm);
		ft_printer(lst, size, key.g);
		teatime = ctime(&lst->mtime);
		//printf("  %s  ", teatime);
		print_time(teatime);
		ft_putchar(' ');
		ft_putstr(lst->name);
		if (perm[0] == 'l')
		{
			ft_putstr(" -> ");
			ft_bzero(buf, NAME_MAX);
			readlink(lst->path, buf, NAME_MAX);
			ft_putstr(buf);
		}	
		ft_putchar('\n');
		lst = lst->next;
	}
}
