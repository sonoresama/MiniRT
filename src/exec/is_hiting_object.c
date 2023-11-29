/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hiting_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:40:58 by eorer             #+#    #+#             */
/*   Updated: 2023/11/29 13:13:04 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	is_hiting_sphere(t_ray ray, t_sphere *sphere)
{
	float	a;
	float	b;
	float	c;
	t_vect	oc;
	float	d;

	oc = ray.origin.xyz - sphere->center.xyz;
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, oc);
	c = dot(oc, oc) - pow(sphere->diameter / 2, 2);
	d = pow(b, 2) - 4 * a * c;
	if (d < 0.0)
		return (-1);
	return (fmin((-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a)));
}

int	is_cam_on_plane(t_vect point, t_plan *plan)
{
	t_vect	normal;
	t_vect	b;
	float	d;

	b = plan->start;
	normal = ft_normalize(plan->vecteur);
	d = normal.x * b.x + normal.y * b.y + normal.z * b.z;
	if (normal.x * point.x + normal.y * point.y + normal.z * point.z == d)
		return (1);
	return (0);
}

float	is_hiting_plan(t_ray ray, t_plan *plan)
{
	float	p_dot;
	float	t;

	if (is_cam_on_plane(ray.origin, plan))
		return (-1);
	p_dot = dot(ray.direction, ft_normalize(plan->vecteur));
	if (p_dot > 0.0001)
		t = dot(plan->start.xyz - ray.origin.xyz,
				ft_normalize(plan->vecteur)) / p_dot;
	else
		t = -1;
	return (t);
}
