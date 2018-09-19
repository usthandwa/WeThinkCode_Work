/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 14:45:24 by szama             #+#    #+#             */
/*   Updated: 2017/06/03 16:05:58 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1_new;
	unsigned char	*str2_new;
	size_t			index;

	index = 0;
	str1_new = (unsigned char *)s1;
	str2_new = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (index < (n - 1))
	{
		if (str1_new[index] == str2_new[index])
			index++;
		else
			return (str1_new[index] - str2_new[index]);
	}
	return (str1_new[index] - str2_new[index]);
}
