/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_stlex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 19:14:51 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 11:28:36 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_req	*ft_shift_size(t_req *files)
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

t_req			*key_big_size(t_req *fls)
{
	if (!fls)
		return (NULL);
	fls->next = key_big_size(fls->next);
	if (fls->next != NULL && fls->size < fls->next->size)
		fls = ft_shift_size(fls);
	return (fls);
}

static t_req	*ft_shift_lex(t_req *lst)
{
	t_req	*r;
	t_req	*l;
	t_req	*head;

	l = lst;
	r = lst->next;
	head = r;
	while (r != NULL && ft_strcmp(lst->name, r->name) > 0)
	{
		l = r;
		r = r->next;
	}
	l->next = lst;
	lst->next = r;
	return (head);
}

t_req			*ft_lex_sort(t_req *fls)
{
	if (!fls)
		return (NULL);
	fls->next = ft_lex_sort(fls->next);
	if (fls->next != NULL && ft_strcmp(fls->name, fls->next->name) > 0)
		fls = ft_shift_lex(fls);
	return (fls);
}
