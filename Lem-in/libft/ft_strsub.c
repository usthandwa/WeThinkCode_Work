/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 11:05:10 by szama             #+#    #+#             */
/*   Updated: 2017/11/28 13:53:41 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	index;

	index = 0;
	if (s)
	{
		new_str = ft_strnew(len);
		if (new_str)
		{
			if (start < ft_strlen(s) && len <= ft_strlen(s))
			{
				while (index < len)
				{
					new_str[index] = s[start + index];
					index++;
				}
				new_str[index] = '\0';
				return (new_str);
			}
		}
	}
	return (NULL);
}
