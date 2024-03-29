/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 11:51:10 by student           #+#    #+#             */
/*   Updated: 2020/07/16 15:07:37 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <dirent.h>
# include <limits.h>
# include <time.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <uuid/uuid.h>
# include <pwd.h>
# include <grp.h>
# include <sys/ioctl.h>
# include "libft.h"
# include <errno.h>
# include <stdio.h>

# define OPTIONS ("RalrtugfdiUs1xSA")

# define MAX(a, b)		b & ((a - b) >> 31) | a & (~(a - b) >> 31)
# define ABS(a)			(a ^ (a >> 31)) - (a >> 31)
# define CLEAR(a, b)	((a) &= (~(b)))

# define L_1		4100
# define X_1		12288
# define U_U		2080
# define X_L		8196
# define G_1		4160
# define G_X		8256
# define L_G		68
# define K_RR		1
# define K_A		2
# define K_L		4
# define K_R		8
# define K_T		16
# define K_U		32
# define K_G		64
# define K_F		128
# define K_D		256
# define K_I		512
# define K_UU		1024
# define K_S		2048
# define K_1		4096
# define K_X		8192
# define K_SS		16384
# define K_AA		32768

typedef struct stat	t_stat;

typedef struct		s_req
{
	char			path[PATH_MAX];
	mode_t			mode;
	nlink_t			num_link;
	off_t			size;
	uid_t			own_uid;
	gid_t			grp_gid;
	dev_t			req_dev;
	ino_t			inode;
	blkcnt_t		block;
	time_t			mtime;
	time_t			atime;
	time_t			btime;
	char			*name;
	struct s_req	*next;
	struct s_req	*right;
}					t_req;

void				ft_err(int i, char *av);
int					ft_looker(char **const av, int const ac, int *c);
t_req				*fill_list(char **av, int f, int *stage);
t_req				*ft_parse_av(t_req *files, int key, int ac, int c);
int					add_file(char path[PATH_MAX], char *name, t_req **head);
t_req				*handle_nodir(t_req *files, int key, int *stage);
t_req				*ft_distributer(t_req *lst, int key, int stage);
t_req				*swap_nodes(t_req *node1, t_req *node2);
t_req				*ft_print_files(t_req *lst, int key);
int					len_num(int n);
void				ft_zero(int *arr, int i);
int					ft_check_dots(const char *s1);
void				ft_free_sky(t_req *head);
t_req				*ft_buff_err(t_req **head, char *name, int *flag);
void				ft_handle_err(t_req *head, int f);
int					ft_is_key(int inos, int max);
void				ft_put_link(char path[PATH_MAX]);
int					ft_summ_blocksize(t_req *fls);
t_req				*ft_sorting(t_req *lst, int key);
t_req				*key_u_access(t_req *fls);
t_req				*key_r_reverse(t_req *fls);
t_req				*key_big_size(t_req *fls);
t_req				*key_t_time(t_req *files);
t_req				*key_birth(t_req *fls);
t_req				*ft_lex_sort(t_req *fls);
void				ft_key_l(t_req *fls, int key);
void				ft_column_y(t_req *lst, int key);
void				ft_mode(int mode, char str[11]);
void				ft_pw_uid(struct passwd *data, int size, unsigned int num);
void				ft_gr_gid(struct group *data, int size, unsigned int num);
int					ft_calc_uid(t_req *fls, int max);
int					ft_calc_gid(t_req *fls, int max);
void				ft_special(t_req *fls, int size[8]);
int					ft_check_link(t_req *lst, char a);

#endif
