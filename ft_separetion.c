#include "ft_ls.h"

t_req	*handle_nodir(t_req *files, u_keys key, int stage)
{
	t_req	*head;
	t_req	*arg;
	t_req	*tmp;
	t_req	*chc;
	t_req	*prev;

	head = files;
	prev = files;
	arg = NULL;
//	puts("begin separation");
	while (files)
	{
		chc = files->next;
		if (!S_ISDIR(files->mode))
		{
			if (files == head)
				head = head->next;
			else
			{
				prev = head;
				while(prev->next != files)
					prev = prev->next;	
				prev->next = chc;
			}
			files->next = NULL;
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
	if (!stage && arg)
	{
		arg = ft_sorting(arg, key);
		ft_print_files(arg, key);
	}
//	if (stage)
//		ft_print_files(arg, key);
//	puts("end separation");	
	return (head);
}
