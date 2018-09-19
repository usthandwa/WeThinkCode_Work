/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:38:21 by szama             #+#    #+#             */
/*   Updated: 2018/09/05 17:38:23 by szama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

typedef struct		s_links
{
	int				visited;
	char			*str;
	char			**lnk;
	struct s_links	*next;
}					t_links;

typedef struct		s_rooms
{
	char			*room;
	int				visited;
	struct s_rooms	*next;
}					t_rooms;

typedef	struct		s_ant
{
	char			*name;
	t_rooms			*path;
	struct s_ant	*next;
}					t_ant;

typedef struct		s_input
{
	char			*start;
	char			*end;
	int				ants;
	t_rooms			*l_ants;
	t_rooms			*room;
	t_links			*lnk;
}					t_input;

t_rooms				*fcreate(char *room, t_rooms *next);
t_rooms				*fadd(char *room, t_rooms *next);
t_links				*add(char *str, char **room, t_links *next);
char				**_links(t_input *ptr, char *test);
int					handle_err(t_input *in, char *ptr);
void				check_errors(t_input *ptr);
void				del_last(t_rooms **path);
t_rooms				*get_path(t_input *in);
int					in_list(char *str, t_rooms *list);
void				move_ants(t_input *in, t_rooms *path);
void				error();
void				ft_lstprint_fd(t_rooms *a);

#endif
