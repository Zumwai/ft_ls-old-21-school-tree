/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newdim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 21:19:37 by aophion           #+#    #+#             */
/*   Updated: 2019/09/25 19:41:38 by aophion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_newdim(size_t n)
{
	char		**tab;
	size_t		index;

	if (!n || n + 1 < n)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char*) * (n + 1))))
		return (NULL);
	index = 0;
	while (index < n + 1)
	{
		tab[index] = 0;
		index++;
	}
	return (tab);
}
