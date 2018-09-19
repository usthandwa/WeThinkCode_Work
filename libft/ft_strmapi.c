/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 14:12:56 by szama             #+#    #+#             */
/*   Updated: 2018/06/29 14:39:47 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*tmp;
	unsigned	len;

	if (!s || !(tmp = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	len = 0;
	while (*s)
	{
		tmp[len] = (*f)(len, *s++);
		len++;
	}
	tmp[len] = '\0';
	return (tmp);
}
