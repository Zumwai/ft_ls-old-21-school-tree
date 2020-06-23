#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <dirent.h>
# include <stdio.h>
# include <linux/limits.h>
# include <string.h>
# include <time.h>

# define OPTIONS ("RalrtugfdiUs1xSA")

typedef struct stat t_stat;

typedef union	u_keys
{
	uint16_t	flags;
	struct
		{
			unsigned int R :1; //1
			unsigned int a :1; //2
			unsigned int l :1; //3
			unsigned int r :1; //4
			unsigned int t :1; //5
			unsigned int u :1; //6
			unsigned int g :1; //7
			unsigned int f :1; //8
			unsigned int d :1; //9
			unsigned int i :1; //10
			unsigned int U :1; //11
			unsigned int s :1; //12
			unsigned int k_1 :1; //13
			unsigned int x :1; //14
			unsigned int S :1; //15
			unsigned int A :1; //16
		};
} 	u_keys;

typedef struct		s_req
{
	mode_t		mode;
	nlink_t		num_link;
	off_t		size;
	uid_t		own_uid;
	gid_t		grp_gid;
	dev_t		req_dev;
	blkcnt_t	block;
	time_t		time;
	long		ntime;
	char		*name;
	char		path[PATH_MAX];
	struct s_req 	*next;
}			t_req;

void		ft_err(int i);
u_keys		ft_looker(char **const av, const int ac);
t_req		fill_list(char **av, int ac, u_keys key);

#endif
