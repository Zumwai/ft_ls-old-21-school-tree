#include "./includes/ft_ls.h"

static int	map_path(char path[PATH_MAX], char *name, char full_path[PATH_MAX])
{
	int	i;

	i = -1;
	while(path[++i])
		full_path[i]=path[i];
	if (i && i < PATH_MAX)
		if (!(path[0] == '/' && path[1] == '\0'))
			full_path[i++] = '\0';
	while (*name && i < PATH_MAX)
		full_path[i++] = *name++;
	if (i < PATH_MAX)
		full_path = '\0';
	else
		ft_err(7);
	return ((i < PATH_MAX) ? 1 : 0);
}

t_req	*new_entry(char *name, t_stat *stat)
{
	t_req	*new;


	if (!(new = (t_req *)malloc(sizeof(t_req)))
	|| (!(new->name = strdup(name))))			/////STRDUP FROM LIBRARY
		ft_err(6);
	new->mode = stat->st_mode;
	new->num_link = stat->st_nlink;
	new->size = stat->st_size;
	new->own_uid = stat->st_uid;
	new->grp_gid = stat->st_gid;
	new->req_dev = stat->st_rdev;
	new->block = stat->st_blocks;
	new->time = stat->st_mtime;
	new->ntime = stat->st_mtimespec;

	return (new);
}
		

static int	add_file(char *path[PATH_MAX], char *name, t_req **head)
{	
	char	full_path[PATH_MAX];
	t_stat	stat;

	if (!(map_path(path, name, full_path)))
		ft_err(7);
	if (lstat(full_path, &stat) == -1)
		return (0);
	if (!*head)
		*head = new_entry(name, &stat);
	else
	{
		while ((*head)->next)
			(*head) = (*head)->next;
		(*head)->next = new_entry(name, &stat);
	return (1);
}
	

t_req	*fill_list(char	**av, int ac, u_keys key)
{
	t_req	*head;
	int	i;

	head= NULL;
	while(i < ac)
	{
		if(av[i][0] != '-')
		{
				if (!(add_file("", av[i], &head)))
				ft_err(5);
		}
		i++;
	}			
	return (head);
}
