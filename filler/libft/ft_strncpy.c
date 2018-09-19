/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 10:39:12 by szama             #+#    #+#             */
/*   Updated: 2017/06/03 13:57:52 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n)
	{
		if (ft_strlen(src) < n && index < ft_strlen(src))
			dest[index] = src[index];
		if (index > ft_strlen(src))
			dest[index] = '\0';
		else
			dest[index] = src[index];
		index++;
	}
	return (dest);
}
