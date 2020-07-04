#include "./includes/ft_ls.h"

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
	if (temp.r || temp.U)
		(key->U	> key->r) ? (key->U = 0) : (key->r = 0);
	if (temp.x || temp.l)
		(key->x > key->l) ? (key->x = 0) : (key->l = 0);
	if (temp.S || temp.U)
		(key->S > key->U) ? (key->S = 0) : (key->U = 0);
	if (temp.S || temp.t)
		(key->S > key->t) ? (key->S = 0) : (key->t = 0);
	if (temp.U || temp.t)
		(key->U > key->t) ? (key->U = 0) : (key->t = 0);
	if (temp.f || temp.l)
		(key->f > key->l) ? (key->f = 0) : (key->l = 0);
	if (temp.x || temp.k_1)
		(key->x > key->k_1) ? (key->x = 0) : (key->k_1 = 0);
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
			return (0); 	//error exit no such key
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
	unsigned int i;
	

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
			ft_err(4);
		else if (av[i][0] == '-' && av[i][1])
		{
			if(!(ft_check_key(&key, av[i])))
				ft_err(3);
			else
				*c += 1;
		}
		i++;
	}
	return (key);
}
