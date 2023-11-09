/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:32:23 by eorer             #+#    #+#             */
/*   Updated: 2023/11/08 16:28:49 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vect	ft_normalize(t_vect vector)
{
	float	norm;
	t_vect	vect;

	norm = ft_norm(vector);
	if (!norm)
		return (new_vector(0, 0, 0));
	vect.x = vector.x / norm;
	vect.y = vector.y / norm;
	vect.z = vector.z / norm;
	return (vect);
}

float	ft_norm(t_vect vect)
{
	float	norm;

	norm = sqrt(pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2));
	return (norm);
}

t_vect	intersection(t_ray ray, float t)
{
	t_vect	point;

	point = add_vectors(ray.origin, mult(ray.direction, t));
	return (point);
}
