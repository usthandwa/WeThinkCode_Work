/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 13:44:48 by szama             #+#    #+#             */
/*   Updated: 2018/06/29 14:30:39 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t dst_len;
	size_t src_len;

	dst_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (n < dst_len + 1)
		return (src_len + n);
	if (n > dst_len)
		ft_strncat(dest, src, n - dst_len - 1);
	return (dst_len + src_len);
}
