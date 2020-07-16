/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 11:08:01 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 12:56:12 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		map_path(char path[PATH_MAX], char *name, char full[PATH_MAX])
{
	int	i;

	i = -1;
	while (path[++i])
		full[i] = path[i];
	if (i && i < PATH_MAX)
		if (!(path[0] == '/' && path[1] == '\0'))
			full[i++] = '/';
	while (*name && i < PATH_MAX)
		full[i++] = *name++;
	if (i >= PATH_MAX)
		ft_err(7, "Path name too long");
	else
		full[i] = '\0';
	return (0);
}

static t_req	*new_entry(char *name, t_stat *stat, char path[PATH_MAX])
{
	t_req	*new;

	if (!(new = (t_req *)malloc(sizeof(t_req)))
	|| (!(new->name = ft_strdup(name))))
		ft_err(6, name);
	new->mode = stat->st_mode;
	new->num_link = stat->st_nlink;
	new->size = stat->st_size;
	new->own_uid = stat->st_uid;
	new->grp_gid = stat->st_gid;
	new->req_dev = stat->st_rdev;
	new->block = stat->st_blocks;
	new->mtime = stat->st_mtime;
	new->atime = stat->st_atime;
	new->btime = stat->st_birthtime;
	new->inode = stat->st_ino;
	map_path(path, name, new->path);
	new->right = NULL;
	new->next = NULL;
	return (new);
}

int				add_file(char path[PATH_MAX], char *name, t_req **head)
{
	char	full_path[PATH_MAX];
	t_stat	stat;

	map_path(path, name, full_path);
	if (lstat(full_path, &stat))
		return (0);
	if (!*head)
		*head = new_entry(name, &stat, path);
	else
	{
		while ((*head)->next)
			head = &((*head)->next);
		(*head)->next = new_entry(name, &stat, path);
	}
	return (1);
}

t_req			*fill_list(char **av, int f, int *stage)
{
	t_req	*head;
	t_req	*err;
	int		flag;
	int		i;

	head = NULL;
	err = NULL;
	i = 1;
	flag = 0;
	while (av[i])
	{
		if (!(add_file("", av[i], &head)))
			err = ft_buff_err(&err, av[i], &flag);
		i++;
	}
	if (err)
		*stage = 4;
	ft_handle_err(err, f);
	if (!head && !flag)
		add_file("", ".", &head);
	return (head);
}
