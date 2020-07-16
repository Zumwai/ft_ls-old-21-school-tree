/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 12:44:06 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 12:52:23 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_req	*read_inside(char path[PATH_MAX], int key)
{
	struct dirent	*insider;
	DIR				*fold;
	t_req			*head;

	head = NULL;
	if (!(fold = opendir(path)))
	{
		if (errno == 13)
			return (NULL);
		ft_err(8, path);
	}
	while ((insider = readdir(fold)))
	{
		if (key & K_A)
			add_file(path, insider->d_name, &head);
		else if ((key & K_AA) && !ft_check_dots(insider->d_name))
			add_file(path, insider->d_name, &head);
		else if (insider->d_name[0] != '.')
			add_file(path, insider->d_name, &head);
	}
	closedir(fold);
	return (head);
}

t_req			*ft_parse_av(t_req *files, int key, int ac, int c)
{
	t_req	*curs;

	if (!files)
		return (NULL);
	curs = files;
	while (curs)
	{
		if (S_ISDIR(curs->mode) && (c || !ft_check_dots(curs->name)))
		{
			curs->right = read_inside(curs->path, key);
			if (curs->right && (key & K_RR))
				ft_parse_av(curs->right, key, ac, 0);
		}
		curs = curs->next;
	}
	return (files);
}
