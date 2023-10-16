/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:59:15 by eorer             #+#    #+#             */
/*   Updated: 2023/10/16 19:34:16 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//t_vect	get_bg_color(t_data *data);
t_vect	get_sphere_color(t_data *data);
t_vect	ray_color(t_ray ray, t_data *data);

t_vect	get_color(t_ray ray, t_data *data, int depth)
{
	t_hit_point	hit_point;
	t_vect	new_direction;
	t_sphere *ptr;

	if (depth >= MAX_DEPTH)
		return (get_sphere_color(data));
	hit_point = set_closest_obj(ray, data);
	if (hit_point.type == BACKGROUND)
	{
		if (depth == 0)
			return ((t_vect){0, 0, 0});
		else
			return (get_sphere_color(data));
	}
	else if (hit_point.type == SPHERE)
	{
		ptr = (t_sphere *)hit_point.obj;
		new_direction = v_normal_sphere(*ptr, hit_point.point);
		return (get_color(new_ray(hit_point.point, new_direction), data,  depth + 1));
	}
	return ((t_vect){255, 255, 255});
}

t_vect	get_sphere_color(t_data *data)
{
	t_vect	color;
	t_sphere *sphere;

	sphere = (t_sphere *)data->hit_point.obj;
	color.x = sphere->color.x;
	color.y = sphere->color.y;
	color.z = sphere->color.z;
	return (color);
}

int	get_sampled_color(t_vect color)
{
	int	r;
	int	g;
	int	b;

	r = color.x / SAMPLES_PER_PIXEL;
	g = color.y / SAMPLES_PER_PIXEL;
	b = color.z / SAMPLES_PER_PIXEL;
	return (init_color(0, r, g, b));
}

//t_vect	get_bg_color(t_ray ray, t_data *data)
//{
//	int	r;
//	int	g;
//	int	b;
//	t_vect	color;
//
//	r = / SAMPLES_PER_PIXEL;
//	g = bg_color.y / SAMPLES_PER_PIXEL;
//	b = bg_color.z / SAMPLES_PER_PIXEL;
//	return (init_color(0, 0, 0, 0));
//}
