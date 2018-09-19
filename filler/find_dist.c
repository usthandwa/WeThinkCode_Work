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

#include "filler.h"

int		distance(int a, int a2, int b, int b2)
{
	return (ft_abs(a - b) + ft_abs(a2 - b2));
}

t_token	*closest(t_main *m, t_token *t)
{
	int	i;
	int	j;
	int	closest;

	i = -1;
	while (t)
	{
		closest = distance(t->t.y, m->coord.y, t->t.x, m->coord.x);
		while (m->coord.y > ++i)
		{
			j = -1;
			while (m->coord.x > ++j)
			{
				if (m->map[i][j] == ft_tolower(m->optoken))
				{
					if (closest > distance(t->t.y, i, t->t.x, j))
						closest = distance(t->t.y, i, t->t.x, j);
				}
			}
		}
		t->ds = closest;
		t = t->next;
	}
	return (t);
}

int		placable(t_main *m, t_token **t)
{
	closest(m, *t);
	quick_sort(t);
	return (1);
}

int		find_overlaps(t_main *t_m, int x, int y, t_token *tmp)
{
	int			overlap;
	t_token		*psz;

	overlap = 0;
	psz = tmp;
	while (psz != NULL)
	{
		if (y + psz->t.y < 0 || x + psz->t.x < 0)
			return (0);
		if (y + psz->t.y > t_m->coord.y - 1 || x + psz->t.x > t_m->coord.x - 1)
			return (0);
		if (ft_toupper(t_m->map[y + psz->t.y][x + psz->t.x]) == t_m->token)
			overlap++;
		if (ft_toupper(t_m->map[y + psz->t.y][x + psz->t.x]) == t_m->optoken)
			return (0);
		psz = psz->next;
	}
	return (overlap);
}
