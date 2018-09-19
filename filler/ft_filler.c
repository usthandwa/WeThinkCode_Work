/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:22:54 by szama             #+#    #+#             */
/*   Updated: 2018/07/23 17:23:02 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "filler.h"

int		find_player(char **player, char **line)
{
	get_next_line(0, line);
	if (!ft_strncmp(*line, "$$$ exec ", 9))
	{
		*player = ft_strsub(*line, 9, 2);
		if (ft_strequ("p1", *player))
			return (1);
		else
			return (0);
	}
	else
		perror(strerror(-1));
	return (-1);
}

int		find_token(char **line, t_main *tm, t_token **psz, t_token **tk)
{
	int			x;
	int			y;
	t_token		*tp;

	y = -1;
	tm->map = find_pcoord(line, tm, psz);
	while (++y < tm->coord.y - 1)
	{
		x = -1;
		while (++x < tm->coord.x - 1)
		{
			if (ft_toupper(tm->map[y][x]) == tm->token)
			{
				tp = *psz;
				while (tp)
				{
					if (find_overlaps(tm, x - tp->t.x, y - tp->t.y, *psz) == 1)
						*tk = addco(x - tp->t.x, y - tp->t.y, tk);
					tp = tp->next;
				}
			}
		}
	}
	return (!*tk ? 0 : 1);
}

int		put_piece(char **line, t_main *t_m)
{
	t_token		*psz;
	t_token		*t;

	psz = NULL;
	t = NULL;
	if (find_token(line, t_m, &psz, &t))
	{
		if (t && placable(t_m, &t))
		{
			ft_putnbr(t->t.y);
			ft_putchar(' ');
			ft_putnbr(t->t.x);
			ft_putchar('\n');
		}
		return (1);
	}
	free_stack(&t);
	free_stack(&psz);
	return (0);
}

int		main(void)
{
	char		*line;
	t_main		t_m;
	char		*player;
	int			err;

	err = find_player(&player, &line);
	t_m.token = (err == 1) ? 'O' : 'X';
	t_m.optoken = t_m.token == 'O' ? 'X' : 'O';
	if (err == -1)
		return (-1);
	while (get_next_line(0, &line) > 0)
	{
		if (!put_piece(&line, &t_m))
			ft_putstr("0 0\n");
	}
	free(line);
	free(player);
	return (0);
}
