/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 11:51:50 by szama             #+#    #+#             */
/*   Updated: 2017/09/18 15:14:14 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		find_blksize(t_dir *content)
{
	int			total;
	struct stat	tstat;

	total = 0;
	while (content != NULL)
	{
		lstat(content->f_path, &tstat);
		total += tstat.st_blocks;
		content = content->next;
	}
	return (total);
}

void	do_list(t_env *e)
{
	e->list = (t_dir *)malloc(sizeof(t_dir));
	e->list->dir = ".";
	e->list->next = NULL;
}

void	do_ls(char *dir, t_env *e)
{
	t_dir			*list;
	t_dir			*temp;

	list = NULL;
	if ((e->dirp = opendir(dir)) != NULL)
	{
		while ((e->dp = readdir(e->dirp)) != NULL)
		{
			if (e->dp->d_name[0] != '.' || e->a == 1)
			{
				temp = (t_dir *)malloc(sizeof(t_dir));
				temp->dir = e->dp->d_name;
				temp->f_path = ft_strjoin(ft_strjoin(dir, "/"), e->dp->d_name);
				lstat(temp->f_path, &e->sb);
				temp->time = e->sb.st_mtime;
				(S_ISDIR(e->sb.st_mode) == 1) ? temp->is_dir = 1 : 0;
				temp->next = list;
				list = temp;
			}
		}
		ft_print_ls(list, e, dir);
		return ;
	}
	else
		ft_file_check(e);
}

void	ft_ls(t_env *e)
{
	t_dir	*temp;

	temp = e->list;
	while (temp != NULL)
	{
		do_ls(temp->dir, e);
		temp = temp->next;
	}
}

void	print_xrights(char *fpath)
{
	int		xattrs;

	xattrs = (int)listxattr(fpath, NULL, 1, XATTR_NOFOLLOW);
	if (xattrs > 0)
		ft_putchar('@');
	else
		ft_putchar(' ');
}
