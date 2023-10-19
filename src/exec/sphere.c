/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:49 by eorer             #+#    #+#             */
/*   Updated: 2023/10/19 18:10:09 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	is_hiting_sphere(t_ray ray, t_sphere *sphere)
{
	float	a;
	float	b;
	float	c;
	t_vect	s_to_ray;
	float	d;

	if (!sphere)
	{
		printf("pas de sphere\n");
		return (-1);
	}
	s_to_ray = sous_vectors(ray.origin, sphere->center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, s_to_ray);
	c = dot(s_to_ray, s_to_ray) - pow(sphere->radius / 2, 2);
	d = pow(b, 2) - 4 * a * c;
	if (d < 0.0)
		return (0);
	return (1);
}
