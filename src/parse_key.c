/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:34:01 by aophion           #+#    #+#             */
/*   Updated: 2020/07/16 13:18:51 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ft_char_comp(char let, const char *opt)
{
	unsigned int i;

	i = 0;
	while (opt[i] != '\0')
	{
		if (!((unsigned char)opt[i] ^ (unsigned char)let))
			return (i);
		i++;
	}
	return (-1);
}

static int		ft_toggler(int *key, int res)
{
	int		temp;

	temp = 0;
	temp |= (1 << res);
	if ((temp & K_X) || (temp & K_L))
		CLEAR(*key, K_L + K_X);
	if ((temp & K_UU) || (temp & K_U))
		CLEAR(*key, U_U);
	if ((temp & K_X) || (temp & K_1))
		CLEAR(*key, X_1);
	if ((temp & K_L) || (temp & K_1))
		CLEAR(*key, L_1);
	if ((temp & K_G) || (temp & K_1))
		CLEAR(*key, G_1);
	if ((temp & K_G) || (temp & K_L))
		CLEAR(*key, L_G);
	temp |= *key;
	return (temp);
}

static int		ft_disable(int *key)
{
	int temp;

	temp = (*key);
	if (temp & K_A)
		CLEAR(temp, K_AA);
	if (temp & K_F)
		temp |= K_A;
	if (temp & K_D)
		CLEAR(temp, K_RR);
	if (temp & K_SS)
		CLEAR(temp, K_T);
	return (temp);
}

static int		ft_check_key(int *key, char *av)
{
	unsigned int	i;
	unsigned int	check;
	int				res;

	i = 1;
	check = 0;
	while (av[i] != '\0')
	{
		res = ft_char_comp(av[i], OPTIONS);
		if (res < 0)
			ft_err(3, av);
		else
			*key = ft_toggler(key, res);
		i++;
	}
	*key = ft_disable(key);
	return (1);
}

int				ft_looker(char **const av, int const ac, int *c)
{
	int		key;
	int		i;

	i = 1;
	key = 0;
	while (i < ac)
	{
		if (av[i][0] != '-')
			return (key);
		if (av[i][0] == '-' && av[i][1] == '-' && !av[i][2])
		{
			*c += 1;
			return (key);
		}
		else if (av[i][0] == '-' && av[i][1] == '-' && av[i][2])
			ft_err(4, av[i]);
		else if (av[i][0] == '-' && av[i][1])
		{
			ft_check_key(&key, av[i]);
			*c += 1;
		}
		i++;
	}
	return (key);
}
