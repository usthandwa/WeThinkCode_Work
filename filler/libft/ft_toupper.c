/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:33:17 by szama             #+#    #+#             */
/*   Updated: 2017/06/10 16:33:32 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_toupper(int c)
{
	if (ft_isalpha(c) == 1)
	{
		if (c >= 'a' && c <= 'z')
			return (c - 32);
		else
			return (c);
	}
	else
		return (c);
}
