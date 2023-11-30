/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:27:09 by blerouss          #+#    #+#             */
/*   Updated: 2023/11/30 17:37:10 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vect	v_normal_cy(t_vect point, t_cylinder *cylinder, t_ray ray);
void	set_hit_cy(t_vect data, t_cylinder *cylinder, t_hit *hit, t_ray ray);
void	setup_caps(t_plan *pl_up, t_plan *pl_down, t_cylinder *cylinder);

int	is_hiting_cap(t_ray ray, t_plan plan, t_cylinder *cylinder, float *t)
{
	float	d;
	t_vect	normal;
	t_vect	point;

	normal = ft_normalize(plan.vecteur);
	d = dot(normal, ray.direction);
	if (d == 0)
		return (0);
	*t = dot(plan.start.xyz - ray.origin.xyz, normal) / d;
	point = intersection(ray, *t);
	if (ft_norm(point.xyz - plan.start.xyz) <= cylinder->diameter / 2)
		return (1);
	return (0);
}

float	is_hiting_core(t_ray ray, t_cylinder *cylinder)
{
	float	r[4];
	float	t[2];
	t_vect	u;
	t_vect	v;

	u = cross(cross(cylinder->vecteur, ray.direction), cylinder->vecteur);
	v = cross(cross(cylinder->vecteur, ray.origin.xyz - cylinder->center.xyz),
			cylinder->vecteur);
	r[0] = dot(u, u);
	r[1] = 2 * dot(u, v);
	r[2] = dot(v, v) - pow(cylinder->diameter / 2, 2);
	r[3] = r[1] * r[1] - 4 * r[0] * r[2];
	if (r[3] < 0)
		return (-1);
	t[0] = (-r[1] - sqrt(r[3])) / (2 * r[0]);
	t[1] = (-r[1] + sqrt(r[3])) / (2 * r[0]);
	if (t[0] < 0.001 || (t[1] > 0.001 && (t[1] < t[0])))
		return (t[1]);
	else
		return (t[0]);
}

// avant modification : if t != -1 au lieu de if t < 0
float	is_hiting_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *hit)
{
	t_plan	pl_up;
	t_plan	pl_down;
	float	t;
	t_vect	point;

	if (!cylinder)
		return (-1);
	setup_caps(&pl_up, &pl_down, cylinder);
	if (is_hiting_cap(ray, pl_up, cylinder, &t)
		&& (hit->time == 0 || t < hit->time))
		set_hit_cy(new_vector(t, TOP, 0), cylinder, hit, ray);
	if (is_hiting_cap(ray, pl_down, cylinder, &t)
		&& (hit->time == 0 || t < hit->time))
		set_hit_cy(new_vector(t, BOT, 0), cylinder, hit, ray);
	t = is_hiting_core(ray, cylinder);
	point = intersection(ray, t);
	if (t > 0
		&& pow(ft_norm(sous_vectors(point, cylinder->center)), 2)
		<= pow(cylinder->height / 2, 2) + pow(cylinder->diameter / 2, 2)
		&& (hit->time == 0 || t < hit->time))
		set_hit_cy(new_vector(t, CORE, 0), cylinder, hit, ray);
	if (hit->time > 0.01)
		return (hit->time);
	return (-1);
}

void	get_closest_cylinder(t_ray ray, t_cylinder *cylinder,
		t_hit *first_hit_point)
{
	if (!cylinder)
		return ;
	while (cylinder)
	{
		is_hiting_cylinder(ray, cylinder, first_hit_point);
		cylinder = cylinder->next;
	}
}
