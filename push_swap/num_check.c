/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:22:54 by szama             #+#    #+#             */
/*   Updated: 2018/07/23 17:23:02 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

int		ft_min(t_list **head)
{
	t_list	*tmp;
	int		min;

	tmp = *head;
	min = *(int *)tmp->content;
	while (tmp)
	{
		min = MIN(*(int *)tmp->content, min);
		tmp = tmp->next;
	}
	return (min);
}

int		ft_max(t_list **head)
{
	t_list	*tmp;
	int		max;

	tmp = *head;
	max = *(int *)tmp->content;
	while (tmp)
	{
		max = MAX(*(int *)tmp->content, max);
		tmp = tmp->next;
	}
	return (max);
}

int		first(t_list **head)
{
	return (*(int *)(*head)->content);
}

int		next(t_list **head)
{
	return (*(int *)(*head)->next->content);
}

int		get_position(t_list **stack, int value)
{
	t_list		*current;
	int			position;

	current = *stack;
	position = 0;
	while (current != NULL)
	{
		if (*(int *)current->content == value)
			break ;
		position++;
		current = current->next;
	}
	return (position);
}
