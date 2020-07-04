#include "ft_ls.h"

t_req	*handle_nodir(t_req *files, u_keys key)
{
	t_req	*head;
	t_req	*arg;
	t_req	*tmp;
	t_req	*chc;

	head = files;
	arg = NULL;
	while (files)
	{
		chc = files->next;
		if (!S_ISDIR(files->mode))
		{
			if (files == head)
				head = head->next;
			if (files->next != NULL)
				files->next->prev = files->prev;
			if (files->prev != NULL)
				files->prev->next = files->next;
			files->next = NULL;
			files->prev =  NULL;
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
	ft_distributer(arg, key);
	return (head);
}
