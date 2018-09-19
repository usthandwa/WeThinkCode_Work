/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 11:58:52 by szama             #+#    #+#             */
/*   Updated: 2017/06/22 12:01:39 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_w(char const *s, char *c)
{
	int		i;
	int		j;
	int		word;

	i = 0;
	j = 0;
	word = 0;
	if (ft_strstr((char *)s, c) == NULL)
		return (1);
	while (s[i])
	{
		while (s[i] != c[0] && s[i])
		{
			j++;
			i++;
		}
		if (j != 0 && ((s[i] == c[0]) || s[i] == '\0'))
		{
			j = 0;
			word++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (word);
}

static int		count_c(char const *s, char c)
{
	int		letter;
	int		i;

	letter = 0;
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		letter++;
	}
	return (letter);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		n_words;
	int		i;
	char	n_c[1];

	i = 0;
	n_c[0] = c;
	if (s == NULL)
		return (NULL);
	n_words = count_w(s, n_c);
	if (!(str = (char **)malloc(sizeof(char *) * (n_words + 1))))
		return (NULL);
	if (s[0] == '\0')
		str[i] = ft_strsub(s, 0, count_c(s, c));
	while (n_words-- && s[0] != '\0')
	{
		while (*s == c && *s)
			s++;
		str[i] = ft_strsub(s, 0, count_c(s, c));
		s = s + count_c(s, c);
		i++;
	}
	str[i] = NULL;
	return (str);
}
