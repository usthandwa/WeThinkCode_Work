/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lslong.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 11:48:44 by szama             #+#    #+#             */
/*   Updated: 2017/09/18 15:17:19 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_time(struct stat fstat, t_dir *temp)
{
	char	buff[13];
	char	*str;
	char	buf[64];
	size_t	len;

	(void)fstat;
	str = ctime(&temp->time);
	ft_memcpy(buff, &str[4], 12);
	buff[12] = '\0';
	ft_putstr(buff);
	ft_putstr(" ");
	ft_putstr(temp->dir);
	if (S_ISLNK(fstat.st_mode))
	{
		ft_putstr(" -> ");
		len = readlink(temp->f_path, buf, 64);
		buf[len] = '\0';
		ft_putstr(buf);
	}
}

int		ft_print_stat(char *bytes, int i)
{
	int len;

	len = ft_strlen(bytes);
	while (i-- > len)
		ft_putchar(' ');
	ft_putstr(ft_strjoin(bytes, " "));
	return (0);
}

char	*get_user(struct stat fstat)
{
	char			*str;
	struct passwd	*pw;
	struct group	*gr;

	pw = getpwuid(fstat.st_uid);
	gr = getgrgid(fstat.st_gid);
	str = ft_strjoin(ft_strjoin(pw->pw_name, "  "), gr->gr_name);
	return (ft_strjoin(str, "  "));
}

void	ft_permissions(t_dir *temp, struct stat fstat)
{
	if (temp->is_dir)
		ft_putchar('d');
	else
		ft_putchar((S_ISLNK(fstat.st_mode)) ? 'l' : '-');
	ft_putchar((fstat.st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((fstat.st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((fstat.st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((fstat.st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((fstat.st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((fstat.st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((fstat.st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((fstat.st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((fstat.st_mode & S_IXOTH) ? 'x' : '-');
	print_xrights(temp->f_path);
	ft_putstr(" ");
}

void	print_l(t_dir *list)
{
	t_dir		*temp;
	struct stat	fstat;
	char		*bytes;
	int			i;

	temp = list;
	ft_putendl(ft_strjoin("total ", ft_itoa((find_blksize(temp)))));
	while (temp != NULL)
	{
		lstat(temp->f_path, &fstat);
		ft_permissions(temp, fstat);
		bytes = ft_itoa(fstat.st_nlink);
		i = 2;
		ft_print_stat(bytes, i);
		ft_putstr(get_user(fstat));
		bytes = ft_itoa(fstat.st_size);
		i = 5;
		ft_print_stat(bytes, i);
		get_time(fstat, temp);
		temp = temp->next;
		if (temp != NULL)
			ft_putchar('\n');
	}
}
