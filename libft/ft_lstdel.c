/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 16:51:43 by szama             #+#    #+#             */
/*   Updated: 2018/06/29 16:59:06 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*temp;
	t_list		*lst;

	temp = *alst;
	while (temp)
	{
		lst = temp->next;
		del(temp->content, temp->content_size);
		free(temp);
		temp = lst;
	}
	*alst = NULL;
}
