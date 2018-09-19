/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 15:18:41 by szama             #+#    #+#             */
/*   Updated: 2018/06/30 17:27:50 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_fd(int fd, char **str)
{
	char	*buff;
	char	*temp;
	int		c_read;

	if (!(buff = ft_strnew(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	c_read = read(fd, buff, BUFF_SIZE);
	if (c_read > 0)
	{
		buff[c_read] = '\0';
		temp = ft_strjoin(*str, buff);
		if (!temp)
			return (-1);
		free(*str);
		*str = temp;
	}
	free(buff);
	return (c_read);
}

int			get_line(char **line, char **nline, char **str)
{
	*line = ft_strsub(*str, 0, ft_strlen(*str) - ft_strlen(*nline));
	*nline = ft_strdup(*nline + 1);
	free(*str);
	*str = *nline;
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*str;
	char		*nline;
	int			res;

	if ((!str && (str = ft_strnew(sizeof(*str))) == NULL) || !line)
		return (-1);
	while (!(nline = ft_strchr(str, '\n')))
	{
		if ((res = read_fd(fd, &str)) == 0)
		{
			if (ft_strlen(str) == 0)
				return (0);
			str = ft_strjoin(str, "\n");
		}
		if (res < 0)
			return (-1);
		else
			nline = ft_strchr(str, '\n');
	}
	return (get_line(line, &nline, &str));
}
