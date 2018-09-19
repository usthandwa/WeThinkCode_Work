/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:11:57 by szama             #+#    #+#             */
/*   Updated: 2017/06/11 18:24:15 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_num(int n)
{
	int j;

	j = !n;
	while (n)
	{
		n = n / 10;
		j++;
	}
	return (j);
}

char			*ft_itoa(int n)
{
	char			*str;
	int				len;
	unsigned int	i;

	len = ft_num(n);
	i = n;
	if (n < 0)
	{
		i = -n;
		len++;
	}
	if (!(str = ft_strnew(len)))
		return (NULL);
	str[--len] = i % 10 + '0';
	while (i /= 10)
		str[--len] = i % 10 + '0';
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}
