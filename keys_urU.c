#include "ft_ls.h"

t_req	*key_r_reverse(t_req *fls)
{
	t_req	*foll;
	t_req	*curr;
	t_req	*prev;

	prev = NULL;
	foll = fls;
	curr = fls;
	while(curr)
	{
		foll = foll->next;
		curr->next = prev;
		prev = curr;
		curr = foll;
	}
	return (prev);
}

static t_req	*ft_shift_atime(t_req *fls)
{
	t_req	*r;
	t_req	*l;
	t_req	*head;

	l = fls;
	r = fls->next;
	head = r;
	while (r != NULL && fls->atime > r->atime)
	{
		l = r;
		r = r->next;
	}
	l->next = fls;
	fls->next = r;
	return (head);
}

t_req	*key_u_access(t_req *fls)
{
	if (!fls)
		return (NULL);
	fls->next = key_u_access(fls->next);
	if (fls->next != NULL && fls->atime > fls->next->atime)
		fls = ft_shift_atime(fls);
	return (fls);
}

static	t_req	*ft_shift_birth(t_req	*fls)
{
	t_req	*r;
	t_req	*l;
	t_req	*head;

	l = fls;
	r = fls->next;
	head = r;
	while(r != NULL && fls->btime > r->btime)
	{
		l = r;
		r = r->next;
	}
	l->next = fls;
	fls->next = r;
	return (head);
}


t_req	*key_U_birth(t_req *fls)
{
	if (!fls)
		return (NULL);
	fls->next = key_U_birth(fls->next);
	if (fls->next != NULL && fls->btime > fls->next->btime)
		fls = ft_shift_birth(fls);
	return (fls);
}
