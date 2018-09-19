/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:38:37 by szama             #+#    #+#             */
/*   Updated: 2018/09/05 17:38:39 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void			ft_lstprint_fd(t_rooms *a)
{
	t_rooms		*tmp;

	while (a)
	{
		tmp = a;
		if (tmp && tmp->room)
			ft_putendl(tmp->room);
		if (a)
			a = a->next;
	}
}

void			ft_lstprint(t_links *a)
{
	t_links		*tmp;

	while (a)
	{
		tmp = a;
		if (tmp && tmp->str)
			ft_putendl(tmp->str);
		// if (tmp && tmp->lnk)
		// 	for (int i = 0; tmp->lnk[i]; i++)
		// 		ft_putendl(tmp->lnk[i]);
		if (a)
			a = a->next;
	}
}

void	get_startend(char **map, int i, t_input *in)
{
	if (!in->start && ft_strequ("##start", map[i]))
		in->start = *ft_split(map[++i]);
	else if (!in->end && ft_strequ("##end", map[i]))
		in->end = *ft_split(map[++i]);
}

void	get_info(char *line, t_input *in)
{
	int i;
	char **map;

	i = 0;
	in->ants = 0;
	in->end = NULL;
	map = ft_strsplit(line, '\n');
	//check_errors(map);
	while (map[i])
	{
		ft_putendl(map[i]);
		if (!in->ants && !ft_isnumber(map[i]))
			in->ants = ft_atoi(map[i]);
		else if (ft_strchr(map[i], ' '))
			fadd(ft_split(map[i])[0], in->room);
		else if (ft_strnequ("#", map[i], 0))
			get_startend(map, i, in);
		if (ft_strchr(map[i], '-'))
			in->lnk = add(ft_strdup(map[i]), ft_strsplit(map[i], '-'), in->lnk);
		free(map[i]);
		i++;
	}
	// ft_lstprint_fd(in->room);
	//ft_lstprint(in->lnk);
}

int		main(void)
{
	char	*line;
	t_rooms	*map;
	t_input	*in;

	map = ft_memalloc(sizeof(t_rooms));
	in = ft_memalloc(sizeof(t_input));
	while (get_next_line(0, &line) > 0)
	{
		if (!map->room && !(map->room = ft_memalloc(10)))
			return (1);
		map->room = ft_strjoin(map->room, ft_strcat(line, "\n"));
		free (line);
	}
	get_info(map->room, in);
	move_ants(in, get_path(in));
	free(map);
	free(in);
}
