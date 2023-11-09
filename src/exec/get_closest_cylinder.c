/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:27:09 by blerouss          #+#    #+#             */
/*   Updated: 2023/11/09 16:02:42 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

#define TOP 1
#define BOT 2
#define CORE 3

float	is_hiting_cap(t_ray ray, t_plan plan)
{
	float	d;
	t_vect	normal;

	normal = ft_normalize(plan.vecteur);
	d = dot(normal, ray.direction);
	if (d == 0)
		return (-1);
	return (dot(sous_vectors(plan.start, ray.origin), normal) / d);
}

float	is_hiting_core(t_ray ray, t_cylinder *cylinder)
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	t[2];
	t_vect	u;
	t_vect	v;

	u = cross(cross(cylinder->vecteur, ray.direction), cylinder->vecteur);
	v = cross(cross(cylinder->vecteur, sous_vectors(ray.origin, cylinder->center)), cylinder->vecteur);
	a = dot(u, u);
	b = 2 * dot(v, u);
	c = dot(v, v) - pow(cylinder->diameter / 2, 2);
	d = pow(b, 2) - 4 * a * c;
	if (d < 0)
		return (-1);
	t[0] = (-b - sqrt(d)) / 2 * a;
	t[1] = (-b + sqrt(d)) / 2 * a;
//	if (t[0] < 0.01 || (t[1] > 0.01 && (t[1] < t[0])))
//	if (t[1] < t[0])
//		return (t[1]);
//	else
//		return (t[0]);
		return (fmin((-b + sqrt(d)) / 2 * a, (-b - sqrt(d)) / 2 * a));

}

t_vect	v_normal_cy(t_vect point, t_cylinder *cylinder, t_ray ray)
{
	t_vect	normal;
	t_vect	projection;

	projection = cross(sous_vectors(cylinder->center, point), cylinder->vecteur);
	normal = ft_normalize(cross(projection, cylinder->vecteur));
	if (dot(normal, ray.direction) > 0)
		normal = mult(normal, -1);
	return (normal);
}

void	set_hit_cy(t_cylinder *cylinder, t_vect point, float t, t_hit *hit, int type, t_ray ray)
{
	hit->time = t;
	hit->point = point;
	if (type == TOP)
		hit->normal = cylinder->vecteur;
	else if (type == BOT)
		hit->normal = mult(cylinder->vecteur, -1);
	else
		hit->normal = v_normal_cy(point, cylinder, ray);
	hit->type = CYLINDER;
	hit->obj = cylinder;
	hit->color = cylinder->colors;
}

int	cylinder_inter(t_ray ray, t_cylinder *cylinder, t_hit *hit)
{
	t_plan	pl_up;
	t_plan	pl_down;
	float	t;
	float	dotx;
	t_vect	point;

	if (!cylinder)
		return (0);
	pl_up.vecteur = cylinder->vecteur;
	pl_down.vecteur = mult(cylinder->vecteur, -1);
	pl_up.start = intersection(new_ray(cylinder->center, pl_up.vecteur), cylinder->height / 2);
	pl_down.start = intersection(new_ray(cylinder->center, pl_down.vecteur), cylinder->height / 2);
//	t = is_hiting_cap(ray, pl_up);
//	point = intersection(ray, t);
//	if (t != -1 
//			&& ft_norm(sous_vectors(point, pl_up.start)) <= cylinder->diameter / 2 
//			&& (hit->time == 0 || t < hit->time))
//		set_hit_cy(cylinder, point, t, hit, TOP, ray);
//	t = is_hiting_cap(ray, pl_down);
//	point = intersection(ray, t);
//	if (t != -1 
//			&& ft_norm(sous_vectors(point, pl_down.start)) <= cylinder->diameter / 2 
//			&& (hit->time == 0 || t < hit->time))
//		set_hit_cy(cylinder, point, t, hit, BOT, ray);
	t = is_hiting_core(ray, cylinder);
	if (t != -1)
		printf("t : %f\n", t);
//	if (t != -1 && hit->time == 0)
//	{
//		printf("Only core\n");
//	}
//	if (t != -1 && t < hit->time)
//	{
//		printf("t core : %f\n", t);
//		printf("t hit : %f\n\n", hit->time);
//	}
	point = intersection(ray, t);
	dotx = dot(sous_vectors(point, cylinder->center), cylinder->vecteur) ;
	if (t != -1 
			&& (dotx < -cylinder->height / 2 || dotx > cylinder->height / 2)
			//	&& pow(ft_norm(sous_vectors(cylinder->center, point)), 2) <= pow(cylinder->height / 2, 2) + pow(cylinder->diameter / 2, 2)
			&& (hit->time == 0 || t < hit->time))
		set_hit_cy(cylinder, point, t, hit, CORE, ray);
	if (hit->time > 0.01)
		return (1);
	return (0);
}

//void	get_closest_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *first_hit_point)
//{
//	float	t;
//	t_vect	p;
//
//	while (cylinder)
//	{
//		t = is_hiting_core(ray, cylinder);
//		if (t == -1)
//		{
//			cylinder = cylinder->next;
//			continue;
//		}
//		else
//		{
//			p = intersection(ray, t);
//			if (!first_hit_point->time || (t > 0.01 && t < first_hit_point->time))
//				set_hit_cy(cylinder, intersection(ray, t), t, first_hit_point);
//		}
//		cylinder = cylinder->next;
//	}
//}
