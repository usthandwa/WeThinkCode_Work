/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:39:11 by szama             #+#    #+#             */
/*   Updated: 2018/09/05 17:39:13 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_ant		*save_ants(t_input *ptr)
{
	t_rooms	*head;
	int		i;

	head = NULL;
	i = 1;
	while (i <= ptr->ants)
	{
		head = fadd(ft_strjoin("L", ft_itoa(i)), head);
		if (head->room == NULL || ft_strcmp("\0", head->room) == 0)
			error();
		i++;
	}
	ptr->l_ants = head;
	return ((t_ant *)head);
}

void	start_room(t_input *ptr)
{
	t_rooms		*tmp;

	tmp = ptr->room;
	while (ptr->room->next)
	{
		if (ft_strcmp(ptr->room->room, ptr->start) == 0)
			ptr->room->visited = ptr->ants;
		ptr->room = ptr->room->next;
	}
	ptr->room = tmp;
}

void	print_name(char *name, char *room)
{
	ft_putstr(name);
	ft_putchar('-');
	ft_putstr(room);
	ft_putstr("\n");
}

void	move_ants(t_input *in, t_rooms *path)
{
	t_rooms	*ants;
	t_rooms	*tmp;

	save_ants(in);
	ants = in->l_ants;
	del_last(&path);
	while (ants)
	{
		ft_putstr("\n");
		tmp = path->next;
		while(tmp)
		{
			// handle_err(in, tmp->room);
			print_name(ants->room, tmp->room);
			tmp = tmp->next;
		}
		ants = ants->next;
	}
}
