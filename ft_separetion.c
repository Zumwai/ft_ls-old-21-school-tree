#include "ft_ls.h"

static void	ft_stage(t_req *arg, int *stage, u_keys key)
{
	if (*stage == 0 && arg)
	{
		arg = ft_sorting(arg, key);
		ft_print_files(arg, key);
		(*stage) = 1;
	}
}

static t_req	*ft_delimeter(t_req **files, t_req **head, t_req *prev)
{
	if ((*files) == (*head))
		(*head) = (*head)->next;
	else
	{
		prev = (*head);
		while (prev->next != (*files))
			prev = prev->next;
		prev->next = (*files)->next;
	}
	(*files)->next = NULL;
	return (*files);
}

static t_req	*ft_sep_files(t_req **head, t_req **fls)
{
	t_req	*tmp;


	if (!(*head))
		(*head) = (*fls);
	else
		tmp = (*head);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (*fls);
		tmp->next->next = NULL;
	return (*head);
}
		
t_req	*handle_nodir(t_req *files, u_keys key, int *stage)
{
	t_req	*head;
	t_req	*arg;
	t_req	*tmp;
	t_req	*chc;
	t_req	*prev;

	head = files;
	prev = files;
	arg = NULL;
	while (files)
	{
		chc = files->next;
		if (!S_ISDIR(files->mode))
		{
			files = ft_delimeter(&files, &head, prev);
			arg = ft_sep_files(&arg, &files);
		}
		files = chc;
	}
	ft_stage(arg, stage, key);
	return (head);
}
