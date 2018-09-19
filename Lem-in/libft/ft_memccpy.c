/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 16:19:44 by szama             #+#    #+#             */
/*   Updated: 2017/06/10 02:03:10 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			count;
	unsigned char	*src1;
	unsigned char	*dest1;

	src1 = (unsigned char *)src;
	dest1 = (unsigned char *)dest;
	count = 0;
	while (count < n)
	{
		if (src1[count] != (unsigned char)c)
			dest1[count] = src1[count];
		else
		{
			dest1[count] = src1[count];
			return (&dest1[count + 1]);
		}
		count++;
	}
	return (NULL);
}
