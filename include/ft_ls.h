/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendaou <dbendaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 18:30:51 by dbendaou          #+#    #+#             */
/*   Updated: 2016/05/22 18:38:18 by dbendaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** Includes
*/
# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <sys/xattr.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/acl.h>

/*
** Definition des macros pour options
*/
# define OPT_L		0x1
# define OPT_RC		0x2
# define OPT_A		0x4
# define OPT_RV		0x8
# define OPT_T		0x10
# define ILL_OPT	0x20
# define NO_PRM		0x40

/*
** Definition des macros de test des options
*/
# define IS_L(x)	((x & OPT_L) == OPT_L) ? 1 : 0
# define IS_RC(x)	((x & OPT_RC) == OPT_RC) ? 1 : 0
# define IS_A(x)	((x & OPT_A) == OPT_A) ? 1 : 0
# define IS_RV(x)	((x & OPT_RV) == OPT_RV) ? 1 : 0
# define IS_T(x)	((x & OPT_T) == OPT_T) ? 1 : 0
# define IS_LEG(x)	((x & ILL_OPT) == ILL_OPT) ? 1 : 0
# define IS_USR(x)	((x & S_IXUSR) == S_IXUSR) ? 1 : 0
# define IS_GRP(x)	((x & S_IXGRP) == S_IXGRP) ? 1 : 0
# define IS_OTH(x)	((x & S_IXOTH) == S_IXOTH) ? 1 : 0
# define IS_UID(x)	((x & S_ISUID) == S_ISUID) ? 1 : 0
# define IS_GID(x)	((x & S_ISGID) == S_ISGID) ? 1 : 0
# define IS_STK(x)	((x & S_ISVTX) == S_ISVTX) ? 1 : 0
# define IS_NOPRM(x) (x & NO_PRM) ? 1 : 0

/*
** Structure parametre
*/
typedef struct		s_params
{
	unsigned int	prms;
	int				count;
	char			arg;
}					t_params;

/*
** Structure fichier
*/
typedef struct		s_file
{
	char			f_path[1024];
	char			f_name[1024];
	mode_t			f_mode;
	nlink_t			f_nlink;
	uid_t			f_uid;
	gid_t			f_gid;
	dev_t			f_rdev;
	off_t			f_size;
	blkcnt_t		f_blocks;
	struct timespec	f_time;
	int				error;
	struct s_file	*next;
	struct s_file	*contain;
}					t_file;

typedef struct		s_max
{
	int				m_link;
	int				m_usr;
	int				m_grp;
	int				m_size;
	int				m_maj;
	int				m_min;
	int				m_sprint;
}					t_max;

/*
** append.c
*/
int					readstat(char *path, t_file *file, t_params *params);
void				c_app(char *p, t_file **be, t_params *pr);
void				first_append(char *path, t_file **begin, t_params *params);

/*
** check.c
*/
int					count_dr(t_file *begin);
int					is_nprint(char *name, t_params *params);
int					first_check(t_file *tmp, t_file *new);
int					second_check(t_file *tmp, t_file *new);
int					is_next(t_file *current);

/*
** ft_ls.c
*/
int					ft_ls(int ac, char **av, t_params *params);
char				**get_nextls(t_file *current, int *cnt, t_params *params);
/*
** free.c
*/
void				list_free(t_file **begin);

/*
** get_devsize.c
*/
int					max_min(t_file *to_print, t_params *params);
int					max_maj(t_file *to_print, t_params *params);

/*
** arg_reader.c
*/
t_params			*get_params(int size, char **av);

/*
** list.c
*/
int					dir_list(t_file **current, t_params *params);
t_file				*get_file(int ac, char **av, t_params *params);
int					open_ifdir(t_file **begin, t_params *params);
void				get_l(char *p, t_file **be, struct dirent *b, t_params *pr);
t_file				*open_current(t_params *params, t_file **begin);

/*
** get_pn.c
*/
char				*get_filename(char *path);
char				*get_filepath(char *current, struct dirent *buf);

/*
** reverse.c
*/
t_file				*reverse(t_file *ptr);
void				reverse_list(t_file **to_rev);

/*
** error.c
*/
void				arg_error(char arg);
void				else_error(char *path);
void				stat_error(char *path, t_file *tmp);

/*
** time_append.c
*/
void				t_app(char *p, t_file **be, struct dirent *b, t_params *pr);
void				first_tappend(char *path, t_file **begin, t_params *params);

/*
** printer.c
*/
void				printer(t_file *begin, t_params *params);
int					is_print(t_file *tmp, t_params *params);
int					is_error(t_file *begin);
t_file				*reverse(t_file *ptr);

/*
** lprint.c
*/
void				lprint(t_file *to_print, t_params *params);
void				print_dname(t_file *to_print, t_params *params);
void				print_bonus(t_file *tmp);
void				line_printer(t_file *tmp, t_max *max);

/*
** lprint_gu.c
*/
void				print_nbuid(t_file *to_print, int max);
void				print_usr(t_file *to_print, int max);
void				print_nbgid(t_file *to_print, int max);
void				print_grp(t_file *to_print, int max);

/*
** lprint_oth.c
*/
void				total_print(t_file *to_print, t_params *params);
void				print_nblk(t_file *to_print, int max);
void				print_device(t_file *to_print, t_max *max);
void				print_size(t_file *to_print, t_max *max);
void				date_printer(t_file *to_print);

/*
** openlink.c
*/
int					open_iflink(t_file **current, t_params *params);

/*
** get_max.c
*/
t_max				*get_max(t_file *to_print, t_params *params);

/*
** print_rgt.c
*/
void				print_rights(t_file *tmp);

/*
** recursive.c
*/
void				recursive(t_file **f, t_params *p, int *i, char ***n);
void				l_help(t_file *tmpp, t_file *tmp, t_params *params);

#endif
