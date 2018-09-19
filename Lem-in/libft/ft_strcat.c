/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:16:40 by szama             #+#    #+#             */
/*   Updated: 2017/06/10 16:16:49 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int		index;
	size_t	len;

	index = 0;
	len = ft_strlen(dest);
	while (src[index] != '\0')
	{
		dest[len] = src[index];
		index++;
		len++;
	}
	dest[len] = '\0';
	return ((char *)dest);
}
