/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hiting_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:40:58 by eorer             #+#    #+#             */
/*   Updated: 2023/10/26 15:58:15 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	is_hiting_object(t_data *data, t_ray ray)
{
	t_scene	*scene;

	scene = data->scene;
	while (scene->sphere)
	{
		if (is_hiting_sphere(ray, scene->sphere) != -1)
			return (1);
		scene->sphere = scene->sphere->next;
	}
	while (scene->plan)
	{
		if (is_hiting_plan(ray, scene->plan) != -1)
			return (1);
		scene->plan = scene->plan->next;
	}
	// add cylinder
	return (0);
}

float	is_hiting_sphere(t_ray ray, t_sphere *sphere)
{
	float	a;
	float	b;
	float	c;
	t_vect	s_to_ray;
	float	d;

	s_to_ray = sous_vectors(ray.origin, sphere->center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, s_to_ray);
	c = dot(s_to_ray, s_to_ray) - pow(sphere->diameter / 2, 2);
	d = pow(b, 2) - 4 * a * c;
	if (d < 0.0)
		return (-1);
	return (fmin((-b + sqrt(d)) / 2 * a, (-b - sqrt(d)) / 2 * a));
}

float	is_hiting_plan(t_ray ray, t_plan *plan)
{
	float	p_dot;

	p_dot = dot(ray.direction, ft_normalize(plan->vecteur));
	if (p_dot > 0)
		return (dot(sous_vectors(plan->start, ray.origin), ft_normalize(plan->vecteur)) / p_dot);
	else
		return (-1);
}
