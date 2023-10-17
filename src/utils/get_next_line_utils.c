/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:41:05 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/17 15:22:08 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

int	ft_chrcmp(char *str, char c, int len)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c && i < len)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

void	ft_strlcpy(t_save **ptr_s, t_save **ptr_p, int n)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE - n && (*ptr_p)->save[n + i + 1] != '\0')
	{
		(*ptr_s)->save[i] = (*ptr_p)->save[n + i + 1];
		i++;
	}
	(*ptr_s)->save[i] = '\0';
}

static void	ft_big_join2(t_save **ptr_p, t_save *tmp, char **str, int count)
{
	int	i;

	i = 0;
	while ((*ptr_p))
	{
		count = 0;
		while ((*ptr_p)->save[count])
			(*str)[i++] = (*ptr_p)->save[count++];
		free((*ptr_p)->save);
		tmp = (*ptr_p)->next;
		free((*ptr_p));
		(*ptr_p) = tmp;
	}
	(*str)[i] = '\0';
	if (i == 0)
	{
		free((*str));
		(*str) = NULL;
	}
}

char	*ft_big_join(t_save **ptr_p)
{
	char	*str;
	int		count;
	t_save	*tmp;

	count = 0;
	tmp = (*ptr_p);
	while ((*ptr_p))
	{
		(*ptr_p) = (*ptr_p)->next;
		count++;
	}
	str = malloc(sizeof(char) * (count * BUFFER_SIZE + 1));
	(*ptr_p) = tmp;
	ft_big_join2(&(*ptr_p), tmp, &str, count);
	return (str);
}

t_save	*ft_lstnew(int fd, t_save *prec, int len, t_save **ptr_start)
{
	t_save	*ptr;

	ptr = malloc(sizeof(t_save));
	if (prec)
		prec->next = ptr;
	if (ptr == NULL)
		return (NULL);
	if (!(*ptr_start))
		(*ptr_start) = ptr;
	ptr->prec = prec;
	ptr->fd = fd;
	ptr->save = malloc(sizeof(char) * len + 1);
	ptr->next = NULL;
	return (ptr);
}
