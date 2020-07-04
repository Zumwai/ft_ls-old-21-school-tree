#include "ft_ls.h"

static t_req *key_r_reverse(t_req *fls)
{
	t_req	*foll;
	t_req	*curr;
	t_req	*prev;

	prev = NULL;
	curr = fls;
	foll = fls;

	while(curr != NULL)
	{
		foll = foll->next;
		curr->next = prev;
		prev = curr;
		curr = foll;
	}
	return (prev);
}

int	ft_distributer(t_req *lst, u_keys key)
{
/*
	if (key.flags == 0 || (key.t & 0 && key.u & 0
	&& key.r & 0 && key.t & 0 && key.U & 0 && key.S & 0
	&& key.f & 0))
	*/
	if (key.f)
		return (0);
	/*
	if (key.d == 0)
		if (key.A == 0 || key.a == 0)
			lst = ft_remove_point(lst, key);
	*/
	if(lst)
	{	
		lst = ft_lex_sort(lst);
		if (key.S)
			lst = key_S_size(lst);
		if (key.t || key.u || key.U)
			lst = key_t_time(lst, key);
		if (key.r)
			lst = key_r_reverse(lst);
	}
	while(lst)
	{
		printf("%s\n", lst->name);
		lst = lst->next;
	}
	return (0);
}
