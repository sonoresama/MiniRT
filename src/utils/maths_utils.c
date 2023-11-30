/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:32:23 by eorer             #+#    #+#             */
/*   Updated: 2023/11/29 12:57:19 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vect	ft_normalize(t_vect vector)
{
	float	norm;

	norm = ft_norm(vector);
	if (!norm)
		return (new_vector(0, 0, 0));
	return (vector.xyz / norm);
}

float	ft_norm(t_vect vect)
{
	float	norm;

	norm = sqrt(pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2));
	return (norm);
}

t_vect	intersection(t_ray ray, float t)
{
	return (ray.origin.xyz + t * ray.direction.xyz);
}
