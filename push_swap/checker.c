/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:22:54 by szama             #+#    #+#             */
/*   Updated: 2018/07/23 17:23:02 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

int		valid_arg(char *arg)
{
	return (ft_strequ(arg, "sa") || ft_strequ(arg, "sb") ||
			ft_strequ(arg, "ss") || ft_strequ(arg, "ra") ||
			ft_strequ(arg, "rb") || ft_strequ(arg, "pa") ||
			ft_strequ(arg, "pb") || ft_strequ(arg, "rr") ||
			ft_strequ(arg, "rra") || ft_strequ(arg, "rrb")
			|| ft_strequ(arg, "rrr"));
}

int		getcmd(t_list *a)
{
	char	*cmd;
	t_list	*b;

	cmd = NULL;
	b = NULL;
	while (get_next_line(0, &cmd) > 0 && valid_arg(cmd))
		makeswap(cmd, &a, &b);
	if (cmd && !valid_arg(cmd))
		ft_putendl("error");
	else
		ft_putendl(fsorted(&a, &b) ? "OK" : "KO");
	free(cmd);
	ft_lst_free(&b);
	ft_lst_free(&a);
	return (0);
}

int		main(int c, char **v)
{
	t_list	*a;
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
			ft_strdel(v);
		return (-1);
	}
	ft_addstack(&a, v, c);
	if (free_v)
		ft_strdel(v);
	getcmd(a);
	return (0);
}
