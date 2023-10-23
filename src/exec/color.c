/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:18 by eorer             #+#    #+#             */
/*   Updated: 2023/10/23 16:43:20 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

//t_colors	get_form_color(t_hit *hit_point, t_ray ray)
//{
//	t_sphere	*sphere;
//
//	(void)ray;
//	if (hit_point->type == SPHERE)
//	{
//		sphere = hit_point->obj;
//		return(sphere->colors);
//	}
//	return((t_colors){0,0,0});
//}

t_colors	get_form_color(t_scene *scene, t_hit *hit_point, t_ray ray)
{
	t_sphere	*sphere;
	t_colors	color;
//	t_vect	l_direction;
	float	facing_ratio;

	(void)scene;
//	l_direction = sous_vectors(scene->light->pos, hit_point->point);
	sphere = hit_point->obj;
	color = sphere->colors;
	facing_ratio = fmax(0.0, dot(sphere->normal(*sphere, hit_point->point), mult_const_vector(ray.direction, -1)));
//	facing_ratio = fmax(0.0, dot(sphere->normal(*sphere, hit_point->point), l_direction));
	color.red = facing_ratio * color.red;
	color.green = facing_ratio * color.green;
	color.blue = facing_ratio * color.blue;
	return (color);
}
