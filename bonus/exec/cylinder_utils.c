/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:31:33 by eorer             #+#    #+#             */
/*   Updated: 2023/11/29 13:16:20 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	setup_caps(t_plan *pl_up, t_plan *pl_down, t_cylinder *cylinder)
{
	pl_up->vecteur = cylinder->vecteur;
	pl_down->vecteur = cylinder->vecteur.xyz * -1;
	pl_up->start = intersection(new_ray(cylinder->center, pl_up->vecteur),
			cylinder->height / 2);
	pl_down->start = intersection(new_ray(cylinder->center, pl_down->vecteur),
			cylinder->height / 2);
}

t_vect	v_normal_cy(t_vect point, t_cylinder *cylinder, t_ray ray)
{
	t_vect	normal;
	t_vect	projection;

	projection = cross(cylinder->center.xyz - point.xyz,
			cylinder->vecteur);
	normal = ft_normalize(cross(projection, cylinder->vecteur));
	if (dot(normal, ray.direction) > 0)
		normal = normal.xyz * -1;
	return (normal);
}

void	set_hit_cy(t_vect data, t_cylinder *cylinder, t_hit *hit, t_ray ray)
{
	hit->time = data.x;
	hit->point = intersection(ray, data.x);
	if (data.y == TOP)
		hit->normal = cylinder->vecteur;
	else if (data.y == BOT)
		hit->normal = cylinder->vecteur.xyz * -1;
	else
		hit->normal = v_normal_cy(hit->point, cylinder, ray);
	hit->type = CYLINDER;
	hit->obj = cylinder;
	hit->color = cylinder->colors;
}
