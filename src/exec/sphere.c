/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:49 by eorer             #+#    #+#             */
/*   Updated: 2023/10/20 15:22:55 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	is_hiting_sphere(t_ray ray, t_sphere *sphere);

	// NE PAS OUBLIER DE FREE LE HIT !!!!!!!!!!!!!!!!!!!!!!!!//
t_hit	*get_closest_sphere(t_data *data, t_ray ray)
{
	t_sphere	*tmp;
	t_hit	*hit_point;
	float	min;
	float	t;

	tmp = data->scene->sphere;
	if (!tmp)
		return (NULL);
	hit_point = ft_calloc(sizeof(t_hit), 1);
	if (!hit_point)
		return (data->error = MALLOC_ERR, NULL);
	min = 0;
	while (tmp)
	{
		t = is_hiting_sphere(ray, tmp);
		if (t != -1)
		{
			if (min == 0 || t < min)
			{
				min = t;
				hit_point->obj = tmp;
			}
		}
		tmp = tmp->next;
	}
	if (!min)
		return (NULL);
	hit_point->point = intersection(ray, min);
	hit_point->type = SPHERE;
	return (hit_point);
}

float	is_hiting_sphere(t_ray ray, t_sphere *sphere)
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
		return (-1);
	return (fmin((-b + sqrt(d)) / 2 * a, (-b - sqrt(d)) / 2 * a));
}

t_vect	intersection(t_ray ray, float t)
{
	t_vect	point;

	point = add_vectors(ray.origin, mult_const_vector(ray.direction, t));
	return (point);
}
