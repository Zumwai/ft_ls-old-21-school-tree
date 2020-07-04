#include "ft_ls.h"

static t_req	*ft_shift_size(t_req	*files)
{
	t_req	*n;
	t_req	*p;
	t_req	*ret;

	p = files;
	n = files->next;
	ret = n;
	while (n != NULL && files->size < n->size)
	{
		p = n;
		n = n->next;
	}
	p->next = files;
	files->next = n;
	return (ret);
}

t_req	*key_S_size(t_req *fls)
{
	if (!fls)
		return (NULL);
	fls->next = key_S_size(fls->next);
	if (fls->next != NULL && fls->size < fls->next->size)
		fls = ft_shift_size(fls);
	return (fls);
}

t_req	*key_t_time(t_req *fls, u_keys key)
{
	long int	scope[2];

	if (!fls)
		return (NULL);
	scope[0] = deter_time(fls, key);
	scope[1] = deter_time(fls->next, key);
	if (fls->next != NULL && scope[0] > scope[1])
		fls = swap_nodes(fls, fls->next);
	fls->next = key_t_time(fls->next, key);
	scope[0] = deter_time(fls, key);
	scope[1] = deter_time(fls->next, key);
	if (fls->next != NULL && scope[0] < scope[1])
	{
		fls = swap_nodes(fls, fls->next);
		fls->next = key_t_time(fls->next, key);
	}
	return (fls);
}

t_req	*ft_shift_lex(t_req *lst)
{
	t_req	*r;
	t_req	*l;
	t_req	*head;

	l = lst;
	r = lst->next;
	head = r;
	while (r != NULL && strcmp(lst->name, r->name) > 0)
	{
		l = r;
		r = r->next;
	}
	l->next = lst;
	lst->next = r;
	return (head);
}


t_req	*ft_lex_sort(t_req *fls)
{
	if (!fls)
		return (NULL);
	fls->next = ft_lex_sort(fls->next);
	if (fls->next != NULL && strcmp(fls->name, fls->next->name) > 0) //LIB STRCMP
		fls = ft_shift_lex(fls);
	return (fls);
}
