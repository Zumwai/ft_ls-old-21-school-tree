/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 10:12:11 by aophion           #+#    #+#             */
/*   Updated: 2020/07/15 13:45:29 by aophion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_req	*swap_nodes(t_req *node1, t_req *node2)
{
	node1->next = node2->next;
	node2->next = node1;
	return (node2);
}

int	ft_check_dots(const char *s1)
{
	if (ft_strcmp(s1, "..") && ft_strcmp (s1, "."))
		return (0);	
	return (1);
}

int	ft_summ_blocksize(t_req *fls)
{
	int	total;

	if (fls == NULL)
		return (0);
	total = 0;
	while (fls)
	{
		total +=fls->block;
		fls = fls->next;
	}
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
	return (total);
}

static char	ft_file_type(int mode)
{
	mode = (mode & S_IFMT);
	if (S_ISREG(mode))
		return ('-');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISFIFO(mode))
		return ('p');
	return ('-');
}

void	ft_ACL(int mode, char str[11])
{
	int	i;
	i = 0;

	while (i < 10)
		str[i++] = '-';
	str[0] = ft_file_type(mode);
	if (S_IRUSR & mode)
		str[1] = 'r';
	if (S_IWUSR & mode)
		str[2] = 'w';
	if (S_IXUSR & mode)
		str[3] = 'x';
	if (S_IRGRP & mode)
		str[4] = 'r';
	if (S_IWGRP & mode)
		str[5] = 'w';
	if (S_IXGRP & mode)
		str[6] = 'x';
	if (S_IROTH & mode)
		str[7] = 'r';
	if (S_IWOTH & mode)
		str[8] = 'w';
	if (S_IXOTH & mode)
		str[9] = 'x';
	str[10] = '\0';
	if (S_ISUID & mode)
		str[3] = (str[3] == '-') ? 'S' : 's';
	if (S_ISGID & mode)
		str[6] = (str[6] == '-') ? 'S' : 's';
	if (S_ISVTX & mode)
		str[9] = (str[9] == '-') ? 'T' : 't';
	ft_putstr(str);
}
