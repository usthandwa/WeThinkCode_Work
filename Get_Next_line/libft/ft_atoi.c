/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 13:30:30 by szama             #+#    #+#             */
/*   Updated: 2018/06/29 14:33:53 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		sign;
	long	num;

	sign = 1;
	num = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' && str++)
		if (*str == '-')
			return (0);
	if (*str == '-' && str++)
		sign = -1;
	while (ft_isdigit(*str))
	{
		num = num * 10 + (*str++ - '0');
		if (num < 0)
			return (sign == -1 ? 0 : -1);
	}
	return ((int)num * sign);
}
