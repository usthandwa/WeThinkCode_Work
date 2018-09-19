/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stacks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:22:54 by szama             #+#    #+#             */
/*   Updated: 2018/07/23 17:23:02 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

int		ft_addstack(t_list **a, char **arg, int size)
{
	int	i;
	int	num;

	i = ft_strlen_2d((void **)arg) - 1;
	if (!*a)
	{
		num = atoi(arg[i]);
		*a = ft_lstnew(&num, sizeof(int));
	}
	while (i--)
	{
		if (i < 0)
			return (0);
		if (i < size)
		{
			num = ft_atoi(arg[i]);
			ft_lstadd(a, ft_lstnew(&num, sizeof(int)));
		}
	}
	return (1);
}

void	makeswap(char *cmd, t_list **a, t_list **b)
{
	if (ft_strequ(cmd, "sa"))
		swap(a);
	else if (ft_strequ(cmd, "sb"))
		swap(b);
	else if (ft_strequ(cmd, "ss"))
		sswap(a, b);
	else if (ft_strequ(cmd, "pb"))
		push(a, b);
	else if (ft_strequ(cmd, "pa"))
		push(b, a);
	else if (ft_strequ(cmd, "ra"))
		rot(a);
	else if (ft_strequ(cmd, "rb"))
		rot(b);
	else if (ft_strequ(cmd, "rr"))
		rrot(a, b);
	else if (ft_strequ(cmd, "rra"))
		revrot(a);
	else if (ft_strequ(cmd, "rrb"))
		revrot(b);
	else if (ft_strequ(cmd, "rrr"))
		rrevrot(a, b);
	else
		exit(-1);
}
