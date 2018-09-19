/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:12:19 by szama             #+#    #+#             */
/*   Updated: 2017/06/11 13:03:12 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dest;
	const char	*src2;

	dest = (char*)dst;
	src2 = (const char*)src;
	if (src2 < dest)
	{
		while (len)
		{
			len--;
			dest[len] = src2[len];
		}
	}
	else
		ft_memcpy(dest, src2, len);
	return (dest);
}
