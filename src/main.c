/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 10:43:43 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 13:30:26 by student          ###   ########.fr       */
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

int		main(int ac, char **av)
{
	t_req	*files;
	t_req	*head;
	int		key;
	int		stage;
	int		i;

	i = 0;
	stage = 0;
	files = NULL;
	if (ac > ARG_MAX)
		ft_err(2, "ARG_MAX");
	key = ft_looker(av, ac, &i);
	files = fill_list(&av[i], key, &stage);
	ft_parse_av(files, key, ac - i, 2);
	if (key & K_D)
		ft_print_files(files, key);
	else
		files = ft_distributer(files, key, stage);
	head = files;
	if (head)
		ft_free_sky(head);
	return (0);
}
