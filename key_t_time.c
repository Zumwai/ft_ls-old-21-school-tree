#include "ft_ls.h"

static	t_req	*ft_shift_time(t_req *fls)
{
	t_req	*r;
	t_req	*l;
	t_req	*head;

	l = fls;
	r = fls->next;
	head = r;
	while (r != NULL && fls->mtime > r->mtime)
	{
		l = r;
		r = r->next;
	}
	l->next = fls;
	fls->next = r;
	return (head);
}

t_req	*key_t_time(t_req *fls)
{
	if (!fls)
		return (NULL);
	fls->next = key_t_time(fls->next);
	if (fls->next != NULL && fls->mtime > fls->next->mtime)
		fls = ft_shift_time(fls);
	return (fls);
}
