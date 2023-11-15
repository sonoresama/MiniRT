/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:27:09 by blerouss          #+#    #+#             */
/*   Updated: 2023/11/14 18:46:21 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

#define TOP 1
#define BOT 2
#define CORE 3

int	is_hiting_cap(t_ray ray, t_plan plan, t_cylinder *cylinder, float *t)
{
	float	d;
	t_vect	normal;
	t_vect	point;

	normal = ft_normalize(plan.vecteur);
	d = dot(normal, ray.direction);
	if (d == 0)
		return (0);
	*t = dot(sous_vectors(plan.start, ray.origin), normal) / d;
	point = intersection(ray, *t);
	if (ft_norm(sous_vectors(point, plan.start)) <= cylinder->diameter / 2)
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
	v = cross(cross(cylinder->vecteur, sous_vectors(ray.origin,
					cylinder->center)), cylinder->vecteur);
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

t_vect	v_normal_cy(t_vect point, t_cylinder *cylinder, t_ray ray)
{
	t_vect	normal;
	t_vect	projection;

	projection = cross(sous_vectors(cylinder->center, point),
			cylinder->vecteur);
	normal = ft_normalize(cross(projection, cylinder->vecteur));
	if (dot(normal, ray.direction) > 0)
		normal = mult(normal, -1);
	return (normal);
}

void	set_hit_cy(t_cylinder *cylinder, float t, t_hit *hit, int type, t_ray ray)
{
	hit->time = t;
	hit->point = intersection(ray, t);
	if (type == TOP)
		hit->normal = cylinder->vecteur;
	else if (type == BOT)
		hit->normal = mult(cylinder->vecteur, -1);
	else
		hit->normal = v_normal_cy(hit->point, cylinder, ray);
	hit->type = CYLINDER;
	hit->obj = cylinder;
	hit->color = cylinder->colors;
}

float	is_hiting_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *hit)
{
	t_plan	pl_up;
	t_plan	pl_down;
	float	t;
	t_vect	point;

	if (!cylinder)
		return (-1);
	pl_up.vecteur = cylinder->vecteur;
	pl_down.vecteur = mult(cylinder->vecteur, -1);
	pl_up.start = intersection(new_ray(cylinder->center, pl_up.vecteur), cylinder->height / 2);
	pl_down.start = intersection(new_ray(cylinder->center, pl_down.vecteur), cylinder->height / 2);
	if (is_hiting_cap(ray, pl_up, cylinder, &t)	&& (hit->time == 0 || t < hit->time))
		set_hit_cy(cylinder, t, hit, TOP, ray);
	if (is_hiting_cap(ray, pl_down, cylinder, &t) && (hit->time == 0 || t < hit->time))
		set_hit_cy(cylinder, t, hit, BOT, ray);
	t = is_hiting_core(ray, cylinder);
	point = intersection(ray, t);
	if (t != -1 
			&& pow(ft_norm(sous_vectors(point, cylinder->center)), 2) <= pow(cylinder->height / 2, 2) + pow(cylinder->diameter / 2, 2)
			&& (hit->time == 0 || t < hit->time))
		set_hit_cy(cylinder, t, hit, CORE, ray);
	if (hit->time > 0.01)
		return (hit->time);
	return (-1);
}

void	get_closest_cylinder(t_ray ray, t_cylinder *cylinder,
		t_hit *first_hit_point)
{
	float	t;
	t_hit	*tmp;

	tmp = ft_calloc(sizeof(t_hit), 1);
	if (!tmp)
		return ;
	while (cylinder)
	{
		t = is_hiting_cylinder(ray, cylinder, first_hit_point);
		cylinder = cylinder->next;
	}
	if (tmp->time > 0 && tmp->time < first_hit_point->time)
	{
		first_hit_point->time = tmp->time;
		first_hit_point->point = tmp->point;
		first_hit_point->normal = tmp->normal;
		first_hit_point->type = tmp->type;
		first_hit_point->obj = tmp->obj;
		first_hit_point->color = tmp->color;
	}
	free(tmp);
}
