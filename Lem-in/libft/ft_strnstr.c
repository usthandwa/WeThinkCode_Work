/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:30:30 by szama             #+#    #+#             */
/*   Updated: 2017/06/10 16:30:33 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(to_find) - 1;
	i = 0;
	if (to_find[0] == '\0')
		return (&str[0]);
	else
	{
		while (str[i] && i < n)
		{
			if (str[i] == to_find[0] && str[i + len] == to_find[len])
			{
				while (str[i + len] == to_find[len] && len > 0 && (i + len) < n)
					len--;
				if (len == 0)
					return (&str[i]);
				else
					return (NULL);
			}
			else
				i++;
		}
	}
	return (0);
}
