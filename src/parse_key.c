/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 14:34:01 by aophion           #+#    #+#             */
/*   Updated: 2020/07/15 09:15:25 by aophion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_char_comp(char let, const char *opt)
{
	unsigned int i;

	i = 0;
	while (opt[i] != '\0')
	{
		if(!((unsigned char)opt[i] ^ (unsigned char)let))
			return (i);
		i++;
	}
	return (-1);
}				

static u_keys	ft_toggler(u_keys *key, int res)
{
	u_keys	temp;

	temp.flags = 0;
	temp.flags |= (1 << res);
	if (temp.x || temp.l)
		CLEAR(key->flags, X_L);	
	if (temp.U || temp.u)
		CLEAR(key->flags, U_U);
	if (temp.x || temp.k_1)
		CLEAR(key->flags, X_1);
	if (temp.l || temp.k_1)
		CLEAR(key->flags, L_1);
	temp.flags |= key->flags;
	return (temp);
}

static u_keys ft_disable(u_keys *key)
{
	u_keys temp;

	temp = (*key);
	if (temp.g & 1)
	{
		temp.l = 0;
		temp.k_1 = 0;
	}
	if (temp.l & 1)
		temp.k_1 = 0;
	if (temp.a & 1)
		temp.A = 0;
	if (temp.f & 1)
	{
		temp.u = 0;
		temp.a = 1;
	}
	if (temp.d & 1)
		temp.R = 0;
	if (temp.S & 1)
	{
		temp.t = 0;
		temp.U = 0;
		temp.u = 0;
	}
	return (temp);
}

static int	ft_check_key(u_keys *key, char *av)
{
	unsigned int i;
	unsigned int check;
	int res;

	i = 1;
	check = 0;
	while(av[i] != '\0')
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
			
			

u_keys	ft_looker(char **const av, int const ac, int *c)
{
	u_keys	key;
	int i;

	i = 1;
	key.flags = 0;
	while(i < ac)
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
			if(!(ft_check_key(&key, av[i])))
				ft_err(3, av[i]);
			else
				*c += 1;
		}
		i++;
	}
	return (key);
}
