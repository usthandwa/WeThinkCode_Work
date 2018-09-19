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

void	error()
{
	ft_putendl("ERROR!, Something's Wrong...");
	exit(1);
}

int			is_room_valid(t_input *in, char *str)
{
	int		ret;
	t_rooms *ptr;

	ret = 0;
	ptr = in->room;
	while (ptr)
	{
		if (ft_strcmp(ptr->room, str) == 0)
		{
			ret = 1;
			break ;
		}
		ptr = ptr->next;
	}
	return (ret);
}

void	check_errors(t_input *ptr)
{
	int i;

	i = 0;
	if (ptr->ants == 0 || ptr->start == NULL || ptr->end == NULL)
		i++;
	if (ptr->room == NULL || ptr->lnk == NULL)
	 	i+=2;
	if (ft_strlen_2d((void **)ptr->lnk->lnk) > 2)
		i+=3;
	if (i)
		return (error());
}

int		handle_err(t_input *ptr, char *str)
{
	if (ft_strcmp(str, ptr->end) == 0 || ft_strcmp(str, ptr->start) == 0
	|| is_room_valid(ptr, str) == 0)
		return (1);
	return (0);
}

int			in_list(char *str, t_rooms *list)
{
	t_rooms *tmp;

	tmp = list;
	while (tmp)
	{
		if (ft_strequ(str, tmp->room))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
