/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 17:22:54 by szama             #+#    #+#             */
/*   Updated: 2018/07/23 17:23:02 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"
# include <stdio.h>

typedef struct		s_coordinates
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_token
{
	int				ds;
	t_coord			t;
	struct s_token	*next;
}					t_token;

typedef struct		s_main
{
	char			*player;
	char			token;
	char			optoken;
	char			**map;
	t_coord			coord;
	t_coord			piece;
}					t_main;

t_token				*fcreate(t_token ps, t_token *next);
t_token				*fadd(t_token ps, t_token *next);
char				**find_pcoord(char **line, t_main *t_m, t_token **ps);
t_token				*addco(int a, int b, t_token **dest);
int					placable(t_main *m, t_token **t);
int					find_overlaps(t_main *t_m, int x, int y, t_token *tmp);
void				free_stack(t_token **list);
void				quick_sort(t_token **head);

#endif
