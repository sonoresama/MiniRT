/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:19:22 by eorer             #+#    #+#             */
/*   Updated: 2023/11/29 12:53:43 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vect	new_vector(float x, float y, float z)
{
	return ((t_vect){x, y, z});
}

void	print_vect(t_vect vect)
{
	printf("(%f %f %f)\n", vect.x, vect.y, vect.z);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char	*src;
	size_t	i;

	i = 0;
	src = s;
	while (i < n)
	{
		src[i] = c;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
