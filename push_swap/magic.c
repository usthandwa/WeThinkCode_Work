/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 13:04:32 by szama             #+#    #+#             */
/*   Updated: 2018/08/21 13:04:39 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

int     end(t_list **head)
{
    t_list *tmp;

    tmp = *head;
    while (tmp && tmp->next)
        tmp = tmp->next;
    return (*(int *)tmp->content);
}

char	*sort3(t_list **a)
{
	if (is_sorted(a))
		return ("ok");
	if (first(a) == ft_max(a))
		return ("ra");
	else if (ft_min(a) == next(a))
		return ("sa");
	else
		return ("rra");
}

char	*sortmed(t_list **a, t_list **b)
{
	int	min;

	min = ft_min(a);
	if (fsorted(a, b))
		return ("ok");
	else if (is_sorted(a) && rev_sorted(b))
		return ("pa");
	else if (ft_lstlen(*a) == 3)
		return (fsorted(a, b) ? "ok" : sort3(a));
	else if (next(a) == ft_min(a) && !fsorted(a, b))
			return ("sa");
	else if (end(a) == ft_min(a))
			return ("rra");
	else if (ft_min(a) == first(a) && !fsorted(a, b))
		return ("pb");
	else
		return ((get_position(a, ft_min(a)) <= ft_lstlen(*a) / 2) ? "ra" : "rra");
}

char	*magic(t_list **a, t_list **b, int size)
{
	if (size < 2)
		return ("ok");
	else if (size <= 3)
		return (fsorted(a, b) ? "ok" : sort3(a));
	else //if (size <= 20)
		return (fsorted(a, b) ? "ok" : sortmed(a, b));
	//return (fsorted(a, b) ? "ok" : makesort(a, b));
}
