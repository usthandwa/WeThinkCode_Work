/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 10:41:56 by szama             #+#    #+#             */
/*   Updated: 2018/07/16 13:24:08 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	find_coord(char **line, t_main *t_m)
{
	char	**s;

	if (!ft_strncmp(*line, "Plateau ", 8))
	{
		s = ft_strsplit(*line, ' ');
		t_m->coord.y = ft_atoi(s[1]);
		t_m->coord.x = ft_atoi(s[2]);
		free(*s);
	}
}

void	find_piece(char **line, t_main *t_m)
{
	char	**st;

	get_next_line(0, line);
	if (!ft_strncmp(*line, "Piece ", 6))
	{
		st = ft_strsplit(*line, ' ');
		t_m->piece.y = ft_atoi(st[1]);
		t_m->piece.x = ft_atoi(st[2]);
		free(*st);
	}
}

char	**cpymap(char **line, t_main *t_m)
{
	char		**map;
	int			a;

	a = 0;
	find_coord(line, t_m);
	if (!(map = (char **)malloc(sizeof(char *) * t_m->coord.y)))
		return (NULL);
	get_next_line(0, line);
	while (t_m->coord.y > a)
	{
		get_next_line(0, line);
		map[a] = ft_strdup(*line + 4);
		a++;
	}
	return (map);
}

char	**cpypiece(char **line, t_main *t_m)
{
	char	**piece;
	int		i;

	i = 0;
	find_piece(line, t_m);
	if (!(piece = (char **)malloc(sizeof(char *) * t_m->piece.y)))
		return (NULL);
	while (i < t_m->piece.y)
	{
		if (get_next_line(0, line))
		{
			piece[i] = ft_strdup(*line);
			i++;
		}
	}
	return (piece);
}

char	**find_pcoord(char **line, t_main *t_m, t_token **ps)
{
	int			x;
	int			y;
	char		**temp;
	char		**map;

	y = -1;
	map = cpymap(line, t_m);
	temp = cpypiece(line, t_m);
	while (t_m->piece.y > ++y)
	{
		x = 0;
		while (temp[y][x])
		{
			if (temp[y][x] == '*')
				*ps = addco(x, y, ps);
			x++;
		}
		free(temp[y]);
	}
	return (map);
}
