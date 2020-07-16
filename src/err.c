/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 13:34:57 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 15:11:01 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ft_some_err(void)
{
	ft_putstr_fd("ft_ls: illegal option -- -\nusage: ft_ls [-", 2);
	ft_putstr_fd(OPTIONS, 2);
	ft_putstr_fd("] [file ...]\n", 2);
}

void		ft_err(int i, char *av)
{
	if (i != 4 && i != 3)
	{
		ft_putstr_fd("ft_ls: ", 2);
		if (i != 10)
			ft_putstr_fd(av, 2);
		ft_putstr(": ");
	}
	if (i != 7 && i != 4 && i != 3 && i != 10)
		perror("");
	if (i == 4 || i == 3)
		ft_some_err();
	if (i == 10)
	{
		ft_putstr_fd(strerror(13), 2);
		ft_putchar('\n');
	}
	if (i != 5 && i != 10)
		exit(-1);
}

void		ft_handle_err(t_req *head, int f)
{
	t_req	*tmp;

	if (!head)
		return ;
	if (!(f & K_F))
		head = ft_lex_sort(head);
	tmp = head;
	while (head)
	{
		ft_err(5, head->name);
		head = head->next;
	}
	ft_free_sky(tmp);
}

t_req		*ft_buff_err(t_req **head, char *name, int *flag)
{
	t_req	*new;
	t_req	*tmp;

	if (!(new = (t_req *)malloc(sizeof(t_req)))
	|| (!(new->name = ft_strdup(name))))
		ft_err(6, name);
	new->next = NULL;
	new->right = NULL;
	if (!(*head))
		(*head) = new;
	else
	{
		tmp = (*head);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	*flag = 1;
	return (*head);
}
