/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 14:18:56 by aophion           #+#    #+#             */
/*   Updated: 2019/09/26 13:17:14 by aophion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		j;
	char		*flag;
	size_t		len;

	i = 0;
	j = 0;
	flag = (char *)haystack;
	if (!(len = ft_strlen(needle)))
		return (flag);
	while (haystack[i] != '\0')
	{
		j = 0;
		flag = (char *)&haystack[i];
		while (haystack[i + j] == needle[j] && needle[j] != '\0')
			j++;
		if (needle[j] == '\0')
			return (flag);
		i++;
	}
	return (0);
}
