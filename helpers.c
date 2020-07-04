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
		if (key.u & 1)
			return(fls->atime);
		else if (key.U & 1)
			return(fls->btime);
		else if (key.t & 1)
			return(fls->mtime);
	}
	return(0);
}
