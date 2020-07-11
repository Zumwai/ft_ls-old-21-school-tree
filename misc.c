#include "ft_ls.h"

int	len_num(int n)
{
	int	len;

	len = 1;
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_zero(int *arr, int i)
{
	int k;
	
	k = 0;
	while(k < i)
		arr[k++] = 0;
}

void	ft_pw_uid(struct passwd *data, int size, unsigned int num)
{
	int	len;

	if(!data)
	{
		len = size;
		ft_putnbr(num);
		while(size > len++)
			ft_putchar(' ');
	}
	else
	{
		len = ft_strlen(data->pw_name);
		ft_putstr(data->pw_name);
		while (size > len++)
			ft_putchar(' ');
	}
}

void	ft_gr_gid(struct group *data, int size, unsigned int num)
{
	int	len;

	if (!data)
	{
		len = size;
		ft_putnbr(num);
		while(size > len++)
			ft_putchar(' ');
	}
	else
	{
		len = ft_strlen(data->gr_name);
		ft_putstr(data->gr_name);
		while (size > len++)
			ft_putchar(' ');
	}
}
			
