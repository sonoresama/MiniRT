/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:27:09 by blerouss          #+#    #+#             */
/*   Updated: 2023/11/03 17:12:15 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	is_hiting_core(t_ray ray, t_cylinder *cylinder)
{
	float	a;
	float	b;
	float	c;
	float	d;
	t_vect	u;
	t_vect	v;
	
	u = cross(ray.direction, cylinder->vecteur);
	v = cross(sous_vectors(cylinder->center, ray.origin), cylinder->vecteur);
	a = dot(u, u);
	b = 2 * dot(v, u);
	c = dot(v, v) - pow(cylinder->diameter / 2, 2);
	d = pow(b, 2) - 4 * a * c;
	if (d < 0)
		return (-1);
	else
		return (fmin((-b + sqrt(d)) / 2 * a, (-b - sqrt(d)) / 2 * a));
}

t_vect	v_normal_cy(t_vect point, t_cylinder *cylinder)
{
	t_vect	normal;
	t_vect	projection;
	float	p;

	p = dot(sous_vectors(point, cylinder->center), cylinder->vecteur) / ft_norm(cylinder->vecteur);
	projection = sous_vectors(sous_vectors(point, cylinder->center), mult(cylinder->vecteur, p));
	normal = ft_normalize(projection);
	return (normal);
}

void	set_hit_cy(t_cylinder *cylinder, t_vect point, float t, t_hit *hit)
{
	hit->time = t;
	hit->point = point;
	hit->normal = v_normal_cy(point, cylinder);
	hit->type = CYLINDER;
	hit->obj = cylinder;
	hit->color = cylinder->colors;
}

void	get_closest_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *first_hit_point)
{
	float	t;
	t_vect	p;

	while (cylinder)
	{
		t = is_hiting_core(ray, cylinder);
		if (t == -1)
		{
			cylinder = cylinder->next;
			continue;
		}
		else
		{
			p = intersection(ray, t);
			if (!first_hit_point->time || (t > 0.01 && t < first_hit_point->time))
				set_hit_cy(cylinder, intersection(ray, t), t, first_hit_point);
		}
		cylinder = cylinder->next;
	}
}
