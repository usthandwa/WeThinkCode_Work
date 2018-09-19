/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 11:48:04 by szama             #+#    #+#             */
/*   Updated: 2017/06/11 18:18:35 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*new;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(new = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		new[i] = s[start++];
		i++;
	}
	new[i] = '\0';
	return (new);
}
