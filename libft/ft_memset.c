/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 13:37:34 by szama             #+#    #+#             */
/*   Updated: 2018/06/26 13:37:37 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	tocopy;
	char			*tmp;

	tocopy = (unsigned char)c;
	tmp = (char *)s;
	while (n > 0)
	{
		*tmp = tocopy;
		tmp++;
		n--;
	}
	return (s);
}
