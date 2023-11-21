/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:39:34 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/17 15:21:49 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

static void	ft_init_save(t_save **ptr_s, t_save **ptr_p, int fd, int n)
{
	t_save	*ptr_start;
	t_save	*ptr_prec;

	ptr_start = NULL;
	ptr_start = (*ptr_s);
	ptr_prec = NULL;
	if (!((*ptr_p)->save[n + 1] == '\0'))
	{
		while ((*ptr_s))
		{
			ptr_prec = (*ptr_s);
			(*ptr_s) = (*ptr_s)->next;
		}
		(*ptr_s) = ft_lstnew(fd, ptr_prec, BUFFER_SIZE - n, &ptr_start);
		if ((*ptr_s) == NULL)
			return ;
		ft_strlcpy(&(*ptr_s), &(*ptr_p), n);
		(*ptr_p)->save[n + 1] = '\0';
	}
	if (ptr_prec && ptr_start != (*ptr_s))
		ptr_prec->next = (*ptr_s);
	(*ptr_s) = ptr_start;
}

static int	ft_read2(t_save **ptr_p, int len_read, t_save *ptr_start)
{
	if (len_read < 1)
	{
		free((*ptr_p)->save);
		if ((*ptr_p)->prec)
		{
			(*ptr_p)->prec->next = NULL;
			free((*ptr_p));
			(*ptr_p) = ptr_start;
		}
		else
		{
			free((*ptr_p));
			(*ptr_p) = NULL;
		}
		return (1);
	}
	else
		(*ptr_p)->save[len_read] = '\0';
	return (0);
}

static void	ft_read(int fd, t_save **ptr_p, t_save **ptr_s)
{
	int		len_read;
	int		n;
	t_save	*ptr_tmp;
	t_save	*ptr_start;

	n = -1;
	len_read = BUFFER_SIZE;
	ptr_tmp = NULL;
	ptr_start = (*ptr_p);
	while (n == -1 && len_read == BUFFER_SIZE)
	{
		while ((*ptr_p))
		{
			ptr_tmp = (*ptr_p);
			(*ptr_p) = (*ptr_p)->next;
		}
		(*ptr_p) = ft_lstnew (0, ptr_tmp, BUFFER_SIZE, &ptr_start);
		len_read = read(fd, (*ptr_p)->save, BUFFER_SIZE);
		if (ft_read2(&(*ptr_p), len_read, ptr_start))
			return ;
		n = ft_chrcmp((*ptr_p)->save, '\n', len_read);
		if (n > -1)
			ft_init_save(&(*ptr_s), &(*ptr_p), fd, n);
	}
	(*ptr_p) = ptr_start;
}

static void	ft_pick_save(t_save **ptr_s, int fd, t_save **ptr_p, t_save *start)
{
	while ((*ptr_s))
	{
		if ((*ptr_s)->fd == fd)
		{
			(*ptr_p) = (*ptr_s);
			if ((*ptr_s)->prec)
			{
				if ((*ptr_s)->next)
				{
					(*ptr_s)->prec->next = (*ptr_s)->next;
					(*ptr_s)->next->prec = (*ptr_s)->prec;
				}
				else
					(*ptr_s)->prec->next = NULL;
			(*ptr_s) = start;
			}
			else if ((*ptr_s)->next)
				(*ptr_s) = (*ptr_s)->next;
			else
				(*ptr_s) = NULL;
			return ;
		}
		(*ptr_s) = (*ptr_s)->next;
	}
	(*ptr_s) = start;
}

char	*get_next_line(int fd)
{
	static t_save	*ptr_save = NULL;
	t_save			*ptr_print;
	t_save			*start;

	if (fd < 0 || fd > 999)
		return (NULL);
	ptr_print = NULL;
	start = ptr_save;
	ft_pick_save(&ptr_save, fd, &ptr_print, start);
	if (ptr_print)
	{
		ptr_print->prec = NULL;
		ptr_print->next = NULL;
		if (-1 < ft_chrcmp(ptr_print->save, '\n', BUFFER_SIZE))
			ft_init_save(&ptr_save, &ptr_print, fd,
				ft_chrcmp(ptr_print->save, '\n', BUFFER_SIZE));
		else
			ft_read(fd, &ptr_print, &ptr_save);
	}
	else
		ft_read(fd, &ptr_print, &ptr_save);
	return (ft_big_join(&ptr_print));
}
