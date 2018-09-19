/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 12:33:31 by szama             #+#    #+#             */
/*   Updated: 2017/06/11 12:33:38 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t	index1;
	char	*str2;

	str2 = (char *)str;
	index1 = 0;
	if (len < 1)
		return (str2);
	else
	{
		len--;
		while (index1 <= len)
		{
			str2[index1] = (unsigned char)c;
			index1++;
		}
		return (str2);
	}
}
