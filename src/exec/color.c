/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:18 by eorer             #+#    #+#             */
/*   Updated: 2023/10/20 17:47:04 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_colors	get_form_color(t_scene *scene, t_hit *hit_point, t_ray ray);

int	ray_color(t_data *data, t_ray ray)
{
	t_hit	*hit_point;
	t_colors	color;

	hit_point = get_closest_sphere(data, ray);
	is_hiting_plan(ray, data->scene->plan, hit_point);
	if (!hit_point && data->error == MALLOC_ERR)
		return (-1);
	if (!hit_point)
	{
		free(hit_point);
		return (init_color(0, 0, 0, 0));
	}
	else 
	{
		color = get_form_color(data->scene, hit_point, ray);
		free(hit_point);
		return(init_color(0, color.red, color.green, color.blue));
	}
}

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
