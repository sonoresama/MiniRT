/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:38:27 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/10 10:42:29 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42 
# endif

typedef struct s_save
{
	struct s_save	*prec;
	int				fd;
	char			*save;
	struct s_save	*next;
}		t_save;

t_save	*ft_lstnew(int fd, t_save *prec, int len, t_save **ptr_start);
char	*ft_big_join(t_save **ptr_p);
void	ft_strlcpy(t_save **ptr_s, t_save **ptr_p, int n);
int		ft_chrcmp(char *str, char c, int len);
char	*get_next_line(int fd);

#endif
