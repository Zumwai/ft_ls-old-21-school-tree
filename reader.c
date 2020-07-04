#include "ft_ls.h"

static void	ft_free_lst(t_req *lst)
{
	if (lst->next != NULL)
		ft_free_lst(lst->next);
	free(lst);
	lst=NULL;
}

static t_req	*read_inside(char path[PATH_MAX], char *name, u_keys key)
{
	DIR		*fold;
	struct dirent	*insider;
	t_req		*head;

	head = NULL;
	if (!(fold = opendir(path)))
		ft_err(8);
	if (key.d & 1)
		add_file(path, ".", &head);
	while ((insider = readdir(fold)))
		add_file(path, insider->d_name, &head);
	closedir(fold);
	return (head);
}

static	void TEST_print(t_req *lst)
{
	t_req	*curs;

	curs = lst;
	while(curs)
	{
		printf("%s ", curs->name);
		if (curs->right != NULL)
			TEST_print(curs->right);
		curs = curs->next;
	}
//	ft_free_lst(lst);
}

t_req	*ft_parse_av(t_req *files, u_keys key, int ac, int c)
{
	t_req	*curs;

	curs = files;
	while(curs)
	{
		if (S_ISDIR(curs->mode) && (c || (strcmp(curs->name, ".") && strcmp(curs->name, "..")))) //LIB STRMCMPFEFE
		{
			curs->right = read_inside(curs->path, curs->name, key);
			if(key.R & 1)
				ft_parse_av(curs->right, key, ac, 0);
	//		if(curs->right)
	//			TEST_print(curs->right);	
		}
		curs = curs->next;
	}
	return (files);
}
