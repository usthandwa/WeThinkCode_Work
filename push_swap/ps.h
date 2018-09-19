/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:22:54 by szama             #+#    #+#             */
/*   Updated: 2018/07/23 17:23:02 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_H
# define PS_H
# include "libft/libft.h"
# define MIN(a, b) (((a) < (b)) ? (a) : (b))
# define MAX(a, b) (((a) > (b)) ? (a) : (b))

void	rot(t_list **a);
void	rrot(t_list **a, t_list **b);
void	revrot(t_list **a);
void	rrevrot(t_list **a, t_list **b);
void	swap(t_list **a);
void	sswap(t_list **a, t_list **b);
void	push(t_list **a, t_list **b);

int		ft_min(t_list **head);
int		ft_max(t_list **head);
int		first(t_list **head);
int		next(t_list **head);
int		get_position(t_list **stack, int value);
int		ft_addstack(t_list **a, char **arg, int size);

int		is_sorted(t_list **a);
int		rev_sorted(t_list **b);
int		fsorted(t_list **a, t_list **b);
int		valid(char **v);

void	makeswap(char *cmd, t_list **a, t_list **b);
char	*magic(t_list **a, t_list **b, int size);

#endif
