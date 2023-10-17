/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_vector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:20:01 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/16 16:39:23 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	ft_fill_vector(char *str, t_vect *vector, int line)
{
	char	**pos;

	pos = ft_split(str, ',');
	if (!pos)
		return (printf("%s", MAL_ERR), 1);
	if (ft_atod(pos[0], &vector->x)
		|| ft_atod(pos[1], &vector->y)
		|| ft_atod(pos[2], &vector->z))
		return (ft_free_tab(pos), printf("%s%i\n", POS_ERR, line), 1);
	ft_free_tab(pos);
	return (0);
}
