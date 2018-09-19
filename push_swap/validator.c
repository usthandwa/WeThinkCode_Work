/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:22:54 by szama             #+#    #+#             */
/*   Updated: 2018/07/23 17:23:02 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps.h"

int	duplicate(char **str)
{
	int j;
	int i;

	i = 0;
	j = 1;
	while (str[i] && str[i + 1])
	{
		j = i + 1;
		while (str[j])
		{
			if (ft_strlen(str[i]) == ft_strlen(str[j]))
			{
				if (ft_strequ(str[i], str[j]))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_isnum(char **v)
{
	int i;
	int len;
	int n;

	i = 0;
	if (duplicate(v))
		return (0);
	while (v[i])
	{
		n = ft_atoi(v[i]);
		len = ft_strlen(v[i]);
		len = (v[i][0] == '-' || v[i][0] == '+') ? len + -1 : len;
		if ((n < 0 && !ft_strchr(v[i], '-')) || (n > 0 && ft_strchr(v[i], '-')))
			return (1);
		if (ft_isdigit(v[i][0]) || v[i][0] == '-' || v[i][0] == '+')
		{
			if (len != ft_int_len(ft_atoi(v[i])))
				return (1);
		}
		else
			return (1);
		i++;
	}
	return (0);
}

int	valid(char **v)
{
	if ((ft_isnum(v) && duplicate(v)) || (ft_isnum(v) || duplicate(v)))
		ft_putendl("error");
	return (!ft_isnum(v) && !duplicate(v) ? 1 : 0);
}
