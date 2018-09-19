/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 12:32:30 by szama             #+#    #+#             */
/*   Updated: 2017/06/10 12:32:44 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isnumber(char *v)
{
	int len;
	int n;

	n = ft_atoi(v);
	len = ft_strlen(v);
	len = (v[0] == '-' || v[0] == '+') ? len + -1 : len;
	if ((n < 0 && !ft_strchr(v, '-')) || (n > 0 && ft_strchr(v, '-')))
		return (1);
	if (ft_isdigit(v[0]) || v[0] == '-' || v[0] == '+')
	{
		if (len != ft_int_len(ft_atoi(v)))
			return (1);
	}
	else
		return (1);
	return (0);
}