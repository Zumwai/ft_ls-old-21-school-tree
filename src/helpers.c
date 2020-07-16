/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 10:12:11 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 14:54:40 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_req		*swap_nodes(t_req *node1, t_req *node2)
{
	node1->next = node2->next;
	node2->next = node1;
	return (node2);
}

int			ft_check_dots(const char *s1)
{
	if (ft_strcmp(s1, "..") && ft_strcmp(s1, "."))
		return (0);
	return (1);
}

int			ft_summ_blocksize(t_req *fls)
{
	int	total;

	if (fls == NULL)
		return (0);
	total = 0;
	while (fls)
	{
		total += fls->block;
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

void		ft_mode(int mode, char str[11])
{
	str[0] = ft_file_type(mode);
	str[1] = (S_IRUSR & mode) ? 'r' : '-';
	str[2] = (S_IWUSR & mode) ? 'w' : '-';
	str[3] = (S_IXUSR & mode) ? 'x' : '-';
	str[4] = (S_IRGRP & mode) ? 'r' : '-';
	str[5] = (S_IWGRP & mode) ? 'w' : '-';
	str[6] = (S_IXGRP & mode) ? 'x' : '-';
	str[7] = (S_IROTH & mode) ? 'r' : '-';
	str[8] = (S_IWOTH & mode) ? 'w' : '-';
	str[9] = (S_IXOTH & mode) ? 'x' : '-';
	str[10] = '\0';
	if (S_ISUID & mode)
		str[3] = (str[3] == '-') ? 'S' : 's';
	if (S_ISGID & mode)
		str[6] = (str[6] == '-') ? 'S' : 's';
	if (S_ISVTX & mode)
		str[9] = (str[9] == '-') ? 'T' : 't';
}
