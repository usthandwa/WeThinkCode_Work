/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 17:34:10 by szama             #+#    #+#             */
/*   Updated: 2018/06/26 17:37:34 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t len;
	size_t start;

	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	start = 0;
	while (ft_isspace(s[start]))
		start++;
	while (ft_isspace(s[len]))
		len--;
	return (!s[start] ? "" : ft_strsub(s, start, len - start + 1));
}
