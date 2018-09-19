/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 17:39:04 by szama             #+#    #+#             */
/*   Updated: 2017/07/24 17:49:23 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_notspace_start(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	return ((char *)&s[i]);
}

static char		*ft_notspace_end(char const *s)
{
	size_t	i;

	i = ft_strlen(s) - 1;
	while (i && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i--;
	return ((char *)&s[i]);
}

char			*ft_strtrim(char const *s)
{
	char	*firstword;
	char	*lastword;
	char	*str;
	size_t	len;

	if (!s)
		return (NULL);
	firstword = ft_notspace_start(s);
	lastword = ft_notspace_end(s);
	if (firstword > lastword)
	{
		str = ft_strnew(0);
		if (!str)
			return (NULL);
		return (str);
	}
	len = lastword - firstword + 1;
	str = ft_strnew(len);
	if (!str)
		return (NULL);
	str = ft_strncpy(str, firstword, len);
	return (str);
}
