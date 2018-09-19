/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 16:15:43 by szama             #+#    #+#             */
/*   Updated: 2017/06/10 16:15:48 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *str, int fd)
{
	int index;

	index = 0;
	if (str)
	{
		while (str[index] != '\0')
		{
			ft_putchar_fd(str[index], fd);
			index++;
		}
	}
}
