/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 10:43:43 by aophion           #+#    #+#             */
/*   Updated: 2020/07/15 16:00:24 by aophion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_free_sky(t_req *head)
{
	t_req	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->right)
			ft_free_sky(tmp->right);
		if (tmp)
			free(tmp);
	}
}

int	main(int ac, char **av)
{
	u_keys	key;	
	t_req	*files;
	t_req	*head;
	int	i;
	int	stage;

	i = 0;
	stage = 0;
	files = NULL;
	if (ac > ARG_MAX)
		ft_err(2, "ARG_MAX");
	key = ft_looker(av, ac, &i);
	files = fill_list(&av[i], key.f, &stage);
	ft_parse_av(files, key, ac - i, 2);
	if (key.d)
		ft_print_files(files, key);
	else
		files = ft_distributer(files, key, stage);
	head = files;
	if (head)
		ft_free_sky(head);
	return (0);
}
