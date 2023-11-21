/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hiting_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:40:58 by eorer             #+#    #+#             */
/*   Updated: 2023/11/21 12:38:22 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int		inside_test(t_vect point, t_triangle *triangle, t_vect normal);
void	set_hit_triangle(float t, t_hit *hit_point, t_vect normal,
			t_vect point);

float	is_hiting_sphere(t_ray ray, t_sphere *sphere)
{
	float	a;
	float	b;
	float	c;
	t_vect	oc;
	float	d;

	oc = sous_vectors(ray.origin, sphere->center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, oc);
	c = dot(oc, oc) - pow(sphere->diameter / 2, 2);
	d = pow(b, 2) - 4 * a * c;
	if (d < 0.0)
		return (-1);
	return (fmin((-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a)));
}

float	is_hiting_plan(t_ray ray, t_plan *plan)
{
	float	p_dot;
	float	t;

	p_dot = dot(ray.direction, ft_normalize(plan->vecteur));
	if (p_dot > 0.0001)
		t = dot(sous_vectors(plan->start, ray.origin),
				ft_normalize(plan->vecteur)) / p_dot;
	else
		t = -1;
	return (t);
}

float	inside_tr_plan(t_triangle *triangle, t_ray ray, t_plan *plan)
{
	float	t;
	t_vect	u;
	t_vect	v;
	t_vect	normal;
	float	p_dot;

	u = sous_vectors(triangle->b, triangle->a);
	v = sous_vectors(triangle->c, triangle->a);
	normal = ft_normalize(cross(u, v));
	p_dot = dot(normal, ray.direction);
	if (fabs(p_dot) < 0.001)
		return (-1);
	t = -(dot(ray.origin, normal) - dot(normal, triangle->a)) / p_dot;
	if (t < 0.001)
		return (-1);
	plan->vecteur = normal;
	plan->start = triangle->a;
	plan->colors = triangle->colors;
	return (t);
}

int	is_hiting_triangle(t_ray ray, t_triangle *triangle, t_hit *hit_point)
{
	t_vect	point;
	t_plan	plan;
	float	t;

	ft_bzero(&plan, sizeof(t_plan));
	t = inside_tr_plan(triangle, ray, &plan);
	if (t == -1)
		return (0);
	point = intersection(ray, t);
	if (!inside_test(point, triangle, plan.vecteur))
		return (0);
	set_hit_triangle(t, hit_point, plan.vecteur, point);
	hit_point->obj = triangle;
	hit_point->color = triangle->colors;
	return (1);
}
