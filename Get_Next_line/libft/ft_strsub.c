/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 17:35:27 by szama             #+#    #+#             */
/*   Updated: 2018/06/29 14:40:24 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s || !(ptr = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[start++];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
