/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/21 11:45:46 by szama             #+#    #+#             */
/*   Updated: 2018/08/21 11:45:50 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

void	decide(t_list **a, t_list **b, int size)
{
	char *cmd;

	while (!ft_strequ((cmd = magic(a, b, size)), "ok"))
	{
		ft_putendl(cmd);
		makeswap(cmd, a, b);
	}
	ft_lst_free(a);
}

int		main(int c, char **v)
{
	t_list	*a;
	t_list	*b;
	int		free_v;

	if (c < 2)
		return (-1);
	v = v + 1;
	free_v = (c == 2 && ft_strchr(v[0], ' ')) ? 1 : 0;
	v = (free_v ? ft_split(v[0]) : v);
	c = (free_v ? ft_strlen_2d((void **)v) : c - 1);
	if (!valid(v))
	{
		if (free_v)
			ft_free_array((void **)v);
		return (-1);
	}
	ft_addstack(&a, v, c);
	b = NULL;
	decide(&a, &b, ft_lstlen(a));
	if (free_v)
		ft_free_array((void **)v);
	ft_lst_free(&b);
	return (0);
}
