/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 20:30:48 by szama             #+#    #+#             */
/*   Updated: 2017/11/28 13:55:06 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		index;
	char	*duplicate;

	index = 0;
	duplicate = (char *)malloc(ft_strlen(src) + 1);
	if (duplicate == NULL)
		return (NULL);
	else
	{
		while (src[index] != '\0')
		{
			duplicate[index] = (char)src[index];
			index++;
		}
		duplicate[index] = '\0';
		return (duplicate);
	}
}
