/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 11:49:20 by szama             #+#    #+#             */
/*   Updated: 2017/09/18 14:32:41 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <sys/stat.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>

typedef struct	s_dir
{
	char			*dir;
	time_t			time;
	int				is_dir;
	char			*f_path;
	struct s_dir	*next;
}				t_dir;

typedef struct	s_env
{
	int				l;
	int				a;
	int				r;
	int				t;
	int				rr;
	char			*path;
	DIR				*dirp;
	struct dirent	*dp;
	struct stat		sb;
	t_dir			*list;
}				t_env;

void			ft_ls(t_env *e);
int				ft_file_check(t_env *e);
int				compare_time(t_dir d1, t_dir d2);
void			ft_print_ls(t_dir *list, t_env *e, char *path);
int				compare_time(t_dir d1, t_dir d2);
int				compare_strings(t_dir d1, t_dir d2);
void			do_ls(char *dir, t_env *e);
void			sort_list(t_dir **head, int (*cmp)(t_dir, t_dir), int done);
void			do_list(t_env *e);
void			print_l(t_dir *list);
int				find_blksize(t_dir *list);
void			print_xrights(char *f_path);

#endif
