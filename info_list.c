#include "./includes/ft_ls.h"

static int	map_path(char path[PATH_MAX], char *name, char full_path[PATH_MAX])
{
	int	i;

	i = -1;
	while(path[++i])
		full_path[i]=path[i];
	if (i && i < PATH_MAX)
		if (!(path[0] == '/' && path[1] == '\0'))
			full_path[i++] = '/';
	while (*name && i < PATH_MAX)
		full_path[i++] = *name++;
	if (i < PATH_MAX)
		full_path[i] = '\0';
	else
		ft_err(7, "Path name too long");
	return ((i < PATH_MAX) ? 1 : 0);
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
	new->inode = stat->st_ino;
	new->btime = stat->st_birthtime;
	map_path(path, name, new->path);
	new->right = NULL;
	new->next = NULL;
	return (new);
}
		

int	add_file(char path[PATH_MAX], char *name, t_req **head)
{	
	char	full_path[PATH_MAX];
	t_stat	stat;

	if (!(map_path(path, name, full_path)))
		ft_err(7, "Path name too long");
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

t_req	*fill_list(char	**av, int ac)
{
	t_req	*head;
	int	i;
	int	flag;

	head= NULL;
	i = 1;
	flag = 0;
	while(av[i])
	{
		if(av[i][0] == '-' && av[i][1] == '-')
			flag = 1;
		else if((av[i][0] != '-' && flag == 0) || flag == 1)
			if (!(add_file("", av[i], &head)))
				ft_err(5, av[i]);
		i++;
	}
	if (!head)
		add_file("", ".", &head);
	return (head);
}
