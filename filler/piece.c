/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 10:15:21 by szama             #+#    #+#             */
/*   Updated: 2018/08/14 10:15:55 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_token	*fcreate(t_token co, t_token *next)
{
	t_token	*fnew;

	if (!(fnew = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	fnew->t.x = co.t.x;
	fnew->t.y = co.t.y;
	fnew->next = next;
	return (fnew);
}

t_token	*fadd(t_token co, t_token *next)
{
	t_token	*fnew;
	t_token	*current;

	if (!next)
		return (next = fcreate(co, NULL));
	current = next;
	while (current->next)
		current = current->next;
	fnew = fcreate(co, NULL);
	current->next = fnew;
	return (next);
}

t_token	*addco(int a, int b, t_token **dest)
{
	t_token p_c;

	p_c.t.x = a;
	p_c.t.y = b;
	return (fadd(p_c, *dest));
}

void	free_list(t_token **list)
{
	t_token	*temp;

	if (!*list)
		return ;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp);
		temp = NULL;
	}
}
