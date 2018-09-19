/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:25:32 by szama             #+#    #+#             */
/*   Updated: 2017/08/18 11:22:42 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	int		i;
	int		d_len;
	int		len;
	int		size;

	d_len = 0;
	i = 0;
	len = 0;
	size = n;
	len = ft_strlen(src);
	while (dest[i] && i < size)
		i++;
	d_len = i;
	while (src[i - d_len] && i < size - 1)
	{
		dest[i] = src[i - d_len];
		i++;
	}
	if (d_len < size)
		dest[i] = '\0';
	return (d_len + len);
}
