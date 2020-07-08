#include "ft_ls.h"

t_req	*handle_nodir(t_req *files, u_keys key, int stage)
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
			{
				puts("head");
				head = head->next;
			}
			if (files->next != NULL)
			{
				puts("file next");
				files->next->prev = files->prev;
			}
			if (files->prev != NULL)
			{
				puts("file prev");
				files->prev->next = files->next;
			}
			files->next = NULL;
			files->prev =  NULL;
			if (!arg)
			{
				puts("1 arg");
				arg = files;
			}
			else if (arg)
			{
				puts("arg->next");
				tmp = arg;
				while(tmp->next)
					tmp = tmp->next;
				tmp->next = files;
			}
		}
		files = chc;
	}
	if (!stage)
		ft_print_files(arg, key);
//	if (stage)
//		ft_print_files(arg, key);
		
	return (head);
}
