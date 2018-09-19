/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:22:54 by szama             #+#    #+#             */
/*   Updated: 2018/07/23 17:23:02 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	push(t_list **a, t_list **b)
{
	t_list *temp;

	if (!*a)
		return ;
	if (!*b)
		*b = ft_lstnew((*a)->content, sizeof(int));
	else
		ft_lstadd(b, ft_lstnew((*a)->content, sizeof(int)));
	if ((*a)->next != NULL)
	{
		temp = *a;
		*a = (*a)->next;
		free(temp);
	}
	else
		*a = NULL;
}

void	swap(t_list **a)
{
	t_list *tmp;

	tmp = *a;
	if (tmp->next != NULL)
		ft_swap(tmp->content, tmp->next->content);
}

void	sswap(t_list **a, t_list **b)
{
	swap(a);
	swap(b);
}
