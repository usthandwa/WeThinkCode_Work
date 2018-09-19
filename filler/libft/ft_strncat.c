/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:28:00 by szama             #+#    #+#             */
/*   Updated: 2017/06/10 16:28:04 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	index;
	size_t	len;
	char	nul;

	nul = '\0';
	index = 0;
	len = ft_strlen(dest);
	while (src[index] != '\0')
	{
		if (index < n)
		{
			dest[len] = src[index];
		}
		else
			dest[len] = nul;
		index++;
		len++;
	}
	dest[len] = '\0';
	return (dest);
}
