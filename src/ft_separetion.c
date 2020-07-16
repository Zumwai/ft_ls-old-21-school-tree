/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separetion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:34:57 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 12:48:07 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_req	*ft_add_arg(t_req **arg, t_req **fls)
{
	t_req	*tmp;

	tmp = (*arg);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = (*fls);
	return (*arg);
}

static void		ft_stage(t_req *arg, int **stage, int key)
{
	t_req	*head;

	head = arg;
	if (**stage == 0 || **stage == 4)
	{
		if (arg)
		{
			arg = ft_sorting(arg, key);
			ft_print_files(arg, key);
			ft_free_sky(head);
			(**stage) = 1;
		}
		else if (**stage == 0)
			**stage = 2;
		else
			**stage = 4;
	}
	else if (arg)
		ft_free_sky(head);
}

static t_req	*ft_delimeter(t_req **files, t_req **head)
{
	t_req	*prev;

	if ((*files) == (*head))
		(*head) = (*head)->next;
	else
	{
		prev = (*head);
		while (prev->next != (*files))
			prev = prev->next;
		prev->next = (*files)->next;
	}
	(*files)->next = NULL;
	return (*files);
}

static int		ft_dot(char *name)
{
	if (name[0] == '.' && name[1] == '\0')
		return (1);
	if (name[0] == '.' && name[1] == '.' && name[2] == '\0')
		return (1);
	return (0);
}

t_req			*handle_nodir(t_req *files, int key, int *stage)
{
	t_req	*head;
	t_req	*arg;
	t_req	*tmp;

	head = files;
	arg = NULL;
	while (files)
	{
		tmp = files->next;
		if (!S_ISDIR(files->mode) || (ft_dot(files->name)
		&& !(*stage == 0 || *stage == 4)))
		{
			files = ft_delimeter(&files, &head);
			if (!arg)
				arg = files;
			else
				arg = ft_add_arg(&arg, &files);
		}
		files = tmp;
	}
	ft_stage(arg, &stage, key);
	return (head);
}
