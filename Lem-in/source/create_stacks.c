/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stacks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:39:11 by szama             #+#    #+#             */
/*   Updated: 2018/09/05 17:39:13 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_rooms *fcreate(char *room, t_rooms *next)
{
	t_rooms	*fnew;

	if (!(fnew = ft_memalloc(sizeof(t_rooms))))
		return (NULL);
	fnew->room = room;
	fnew->next = next;
	return (fnew);
}

t_rooms	*fadd(char *room, t_rooms *next)
{
	t_rooms	*fnew;
	t_rooms	*current;

	if (!next)
		return (next = fcreate(room, NULL));
	current = next;
	while (current->next)
		current = current->next;
	fnew = fcreate(room, NULL);
	current->next = fnew;
	return (next);
}

t_links *create(char *str, char **room, t_links *next)
{
	t_links	*fnew;

	if (!(fnew = ft_memalloc(sizeof(t_links))))
		return (NULL);
	fnew->str = str;
	fnew->lnk = room;
	fnew->next = next;
	return (fnew);
}

t_links	*add(char *str, char **room, t_links *next)
{
	t_links	*fnew;
	t_links	*current;

	if (!next)
		return (next = create(str, room, NULL));
	current = next;
	while (current->next)
		current = current->next;
	fnew = create(str, room, NULL);
	current->next = fnew;
	return (next);
}

void		del_last(t_rooms **path)
{
	t_rooms *tmp;
	t_rooms *last;

	tmp = *path;
	if (!tmp || !tmp->next)
		return ;
	last = tmp->next;
	while (last->next)
	{
		tmp = tmp->next;
		last = last->next;
	}
	tmp->next = NULL;
	free(last);
}
