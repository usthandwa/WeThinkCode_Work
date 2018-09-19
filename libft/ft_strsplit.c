/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 17:32:49 by szama             #+#    #+#             */
/*   Updated: 2018/06/29 14:58:04 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *s, char c)
{
	int count;

	count = 0;
	while (s[count])
	{
		if (s[count] == c)
			return (count);
		count++;
	}
	return (count);
}

static int	ft_count(char const *s, char c)
{
	int	count;
	int insub;

	insub = 0;
	count = 0;
	while (*s)
	{
		insub = (insub && *s == c) ? 0 : insub;
		if (!insub && *s != c)
		{
			count++;
			insub = 1;
		}
		s++;
	}
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		elements;
	char	**ptr;

	if (!s)
		return (NULL);
	elements = ft_count(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * (elements + 1))))
		return (NULL);
	ptr = str;
	while (elements--)
	{
		while (*s == c && *s)
			s++;
		*str = ft_strsub(s, 0, ft_len(s, c));
		str++;
		s = s + ft_len(s, c);
	}
	*str = NULL;
	return (ptr);
}
