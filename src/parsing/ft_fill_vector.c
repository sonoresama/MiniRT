/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:20:01 by blerouss          #+#    #+#             */
/*   Updated: 2023/11/29 12:53:21 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	ft_fill_vector(char *str, t_vect *vector, int line)
{
	char	**pos;
	float	x;
	float	y;
	float	z;

	(void)line;
	pos = ft_split(str, ',');
	if (!pos)
		return (printf("%s", MAL_ERR), 1);
	if (ft_tablen(pos) != 3 || ft_count_separator(str, ',') != 2
		|| ft_atod(pos[0], &x)
		|| ft_atod(pos[1], &y)
		|| ft_atod(pos[2], &z))
		return (ft_free_tab(pos), 1);
	*vector = new_vector(x, y, z);
	ft_free_tab(pos);
	return (0);
}
