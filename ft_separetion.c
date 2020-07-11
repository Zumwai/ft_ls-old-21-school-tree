#include "ft_ls.h"

t_req	*handle_nodir(t_req *files, u_keys key, int stage)
{
	t_req	*head;
	t_req	*arg;
	t_req	*tmp;
	t_req	*chc;
	t_req	*prev;

	head = files;
	prev = files;
	arg = NULL;
//	puts("begin separation");
	while (files)
	{
		chc = files->next;
		if (!S_ISDIR(files->mode))
		{
			if (files == head)
				head = head->next;
			else
			{
				prev = head;
				while(prev->next != files)
					prev = prev->next;	
				prev->next = chc;
			}
			files->next = NULL;
			if (!arg)
				arg = files;
			else if (arg)
			{
				tmp = arg;
				while(tmp->next)
					tmp = tmp->next;
				tmp->next = files;
			}
		}
		files = chc;
	}
	if (!stage && arg)
	{
		arg = ft_sorting(arg, key);
		ft_print_files(arg, key);
	}
//	if (stage)
//		ft_print_files(arg, key);
//	puts("end separation");	
	return (head);
}
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

void	ft_pw_uid(struct passwd *data, int size)
{
	int	len;

	if(!data)
	{
		len = size;
		while(len-- > 0)
			ft_putchar(' ');
	}
	else if(data->pw_name)
	{
		len = ft_strlen(data->pw_name);
		while (size > len++)
			ft_putchar(' ');
		ft_putstr(data->pw_name);
	}
	else
	{
		len = len_num(data->pw_uid);
		while (size > len++)
			ft_putchar(' ');
		ft_putnbr(data->pw_uid);
	}
}
			
