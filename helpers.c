#include "ft_ls.h"

t_req	*swap_nodes(t_req *node1, t_req *node2)
{
	t_req	*tmp;

	tmp = node1->prev;
	if (tmp)
		tmp->next = node2;
	node2->prev = tmp;
	node1->prev = node2;
	node1->next = node2->next;
	node2->next = node1;
	if (node1->next != NULL)
		node1->next->prev = node1;
	return (node2);
}

long int	deter_time(t_req *fls, u_keys key)
{
	if (fls)
	{
		if (key.U & 1)
			return(fls->btime);
		 if (key.t & 1)
			return(fls->mtime);
	}
	return(0);
}

t_req	*ft_remove_point(t_req *fls, u_keys key)
{
	t_req	*head;
	t_req	*tmp;

	head = fls;
	while(fls)
	{
		tmp = fls->next;
		if ((strcmp(fls->name, ".") || strcmp(fls->name, ".."))
		&& key.a == 0)
		{
			if (fls == head)
				head = head->next;
			if (fls->next != NULL)
				fls->next->prev = fls->prev;
			if (fls->prev != NULL)
				fls->prev->next = fls->next;
			free(fls);
		}
		fls = tmp;
	}
	return (head);
}

int	ft_check_dots(const char *s1)
{
	if (strcmp(s1, "..") && strcmp (s1, "."))
		return (0);	
//	if ((strncmp(s1, ".", 1) || strncmp (s1, "..", 2)))
//		return (1);
	return (1);
}

