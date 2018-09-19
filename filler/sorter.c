/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 10:16:44 by szama             #+#    #+#             */
/*   Updated: 2018/08/14 10:17:09 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_token	*get_last(t_token *tmp)
{
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

t_token	*move_sort(t_token **tail, t_token **cur, t_token **prev)
{
	t_token *tmp;

	if (*prev)
		(*prev)->next = (*cur)->next;
	tmp = (*cur)->next;
	(*cur)->next = NULL;
	(*tail)->next = (*cur);
	*tail = (*cur);
	return ((*cur) = tmp);
}

t_token	*partition(t_token *head, t_token *end, t_token **nhead, t_token **nend)
{
	t_token *pivot;
	t_token *prev;
	t_token *hold;
	t_token *tail;

	pivot = end;
	prev = NULL;
	hold = head;
	tail = pivot;
	while (hold != pivot)
	{
		if (hold->ds < pivot->ds)
		{
			(*nhead) == NULL ? (*nhead) = hold : (*nhead);
			prev = hold;
			hold = hold->next;
		}
		else
			move_sort(&tail, &hold, &prev);
	}
	if ((*nhead) == NULL)
		(*nhead) = pivot;
	(*nend) = tail;
	return (pivot);
}

t_token	*q_sort_recur(t_token *head, t_token *end)
{
	t_token *newhead;
	t_token *newend;
	t_token *pivot;
	t_token *tmp;

	if (!head || head == end)
		return (head);
	newhead = NULL;
	newend = NULL;
	pivot = partition(head, end, &newhead, &newend);
	if (newhead != pivot)
	{
		tmp = newhead;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = NULL;
		newhead = q_sort_recur(newhead, tmp);
		tmp = get_last(newhead);
		tmp->next = pivot;
	}
	pivot->next = q_sort_recur(pivot->next, newend);
	return (newhead);
}

void	quick_sort(t_token **head)
{
	(*head) = q_sort_recur(*head, get_last(*head));
	return ;
}
