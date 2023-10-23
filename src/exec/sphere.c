/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:49 by eorer             #+#    #+#             */
/*   Updated: 2023/10/23 16:33:33 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static float	is_hiting_sphere(t_ray ray, t_sphere *sphere)
{
	float	a;
	float	b;
	float	c;
	t_vect	s_to_ray;
	float	d;

	s_to_ray = sous_vectors(ray.origin, sphere->center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, s_to_ray);
	c = dot(s_to_ray, s_to_ray) - pow(sphere->radius / 2, 2);
	d = pow(b, 2) - 4 * a * c;
	if (d < 0.0)
		return (-1);
	return (fmin((-b + sqrt(d)) / 2 * a, (-b - sqrt(d)) / 2 * a));
}

void	get_closest_sphere(t_ray ray, t_sphere *sphere, t_hit *first_hit_point)
{
	float	t;

	while (sphere)
	{
		t = is_hiting_sphere(ray, sphere);
		if (t != -1)
		{
			if (first_hit_point->time == 0 || t < first_hit_point->time)
			{
				first_hit_point->time = t;
				first_hit_point->obj = sphere;
			}
		}
		sphere = sphere->next;
	}
	if (!t)
		return ;
	first_hit_point->point = intersection(ray, first_hit_point->time);
	first_hit_point->type = SPHERE;
}
