/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:22:54 by szama             #+#    #+#             */
/*   Updated: 2018/07/23 17:23:02 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	rot(t_list **stack)
{
	t_list	*temp;
	t_list	*hold;

	hold = *stack;
	if (hold && hold->next)
	{
		*stack = (*stack)->next;
		hold->next = NULL;
		temp = *stack;
		while (temp->next)
			temp = temp->next;
		temp->next = hold;
	}
}

void	rrot(t_list **a, t_list **b)
{
	rot(a);
	rot(b);
}

void	revrot(t_list **stack)
{
	t_list *temp;
	t_list *ref_b;

	ref_b = *stack;
	if (!ref_b || !ref_b->next)
		return ;
	while (ref_b->next)
	{
		temp = ref_b;
		ref_b = ref_b->next;
	}
	ref_b->next = *stack;
	temp->next = NULL;
	*stack = ref_b;
}

void	rrevrot(t_list **a, t_list **b)
{
	revrot(a);
	revrot(b);
}
