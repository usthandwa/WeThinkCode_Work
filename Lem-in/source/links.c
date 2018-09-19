/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:39:11 by szama             #+#    #+#             */
/*   Updated: 2018/09/05 17:39:13 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

char 		*find_next(char *current, t_input *in, t_rooms *closedset)
{
	t_links *tmp;

	tmp = in->lnk;
	while (tmp)
	{
		if ((ft_strequ(current, tmp->lnk[0]) || ft_strequ(current, tmp->lnk[1]))
		&& !in_list(tmp->str, closedset))
			return (tmp->str);
		tmp = tmp->next;
	}
	return (NULL);
}

char		*find_prev(t_rooms *path, char *current)
{
	t_rooms *last;
	char	**s;

	last = path;
	while (last->next)
		last = last->next;
	s = ft_strsplit(last->room, '-');
	if (ft_strequ(s[0], current))
		return (s[1]);
	return (s[0]);
}

char		*next(char *link, char *current)
{
	char	**s;

	if (!link)
		return (NULL);
	s = ft_strsplit(link, '-');
	if (ft_strequ(s[0], current))
		return (s[1]);
	return (s[0]);
}

t_rooms		*splitpath(t_rooms *path, t_input *in)
{
	char	*cur;
	t_rooms *tmp;

	cur = in->start;
	tmp = NULL;
	tmp = fcreate(cur, tmp);
	while (path)
	{
		cur = next(path->room, cur);
		tmp = fadd(cur, tmp);
		path = path->next;
	}
	return (tmp);
}

t_rooms		*get_path(t_input *in)
{
	char *current;
	char *tmp;
	t_rooms *path;
	t_rooms *closedset;

	closedset = NULL;
	path = NULL;
	current = in->start;
	while (1)
	{
		ft_putendl(current);
		if (current)
			tmp = find_next(current, in, closedset);
		if (tmp == NULL)
		{
			current = find_prev(path, current);
			if (path || path->next)
				del_last(&path);
			current = next(tmp, current);
			continue ;
		}
		closedset = fadd(tmp, closedset);
		path = fadd(tmp, path);
		if (ft_strequ(current, in->end) || !current)
			break ;
		current = next(tmp, current);
	}
	free(tmp);
	free(current);
	ft_lstprint_fd(path);
	return (splitpath(path, in));
}
