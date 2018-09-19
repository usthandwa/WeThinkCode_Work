/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chksort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:22:54 by szama             #+#    #+#             */
/*   Updated: 2018/07/23 17:23:02 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

int				is_sorted(t_list **a)
{
	t_list *hold;

	if (*a == NULL || (*a)->next == NULL)
		return (1);
	else if ((*a)->next->next == NULL)
		return (*(int *)(*a)->content < *(int *)(*a)->next->content ? 1 : 0);
	else
	{
		hold = *a;
		while (hold && hold->next)
		{
			if (*(int *)hold->content > *(int *)hold->next->content)
				return (0);
			hold = hold->next;
		}
		return (1);
	}
}

int				fsorted(t_list **a, t_list **b)
{
	if (is_sorted(a) && *b == NULL)
		return (1);
	return (0);
}

int				rev_sorted(t_list **b)
{
	t_list *hold;

	if (*b == NULL || (*b)->next == NULL)
		return (1);
	else if ((*b)->next->next == NULL)
		return (*(int *)(*b)->content > *(int *)(*b)->next->content ? 1 : 0);
	else
	{
		hold = *b;
		while (hold && hold->next)
		{
			if (*(int *)hold->content < *(int *)hold->next->content)
				return (0);
			hold = hold->next;
		}
		return (1);
	}
}
