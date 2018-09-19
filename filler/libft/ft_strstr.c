/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 14:18:25 by szama             #+#    #+#             */
/*   Updated: 2017/06/02 14:43:08 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, const char *to_find)
{
	int i_str;
	int len;

	i_str = 0;
	len = ft_strlen(to_find) - 1;
	if (to_find[0] == '\0')
		return (&str[0]);
	else
	{
		while (str[i_str] != '\0')
		{
			if (str[i_str] == to_find[0] && str[i_str + len] == to_find[len])
			{
				while (str[i_str + len] == to_find[len] && len > 0)
					len--;
				if (len == 0)
					return (&str[i_str]);
				len = ft_strlen(to_find) - 1;
				i_str++;
			}
			else
				i_str++;
		}
	}
	return (0);
}
