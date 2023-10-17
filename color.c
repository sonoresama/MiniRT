/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:59:15 by eorer             #+#    #+#             */
/*   Updated: 2023/10/17 17:39:07 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_vect	get_sphere_color(t_hit_point hit_point);
t_vect	ray_color(t_ray ray, t_data *data);

t_vect	a_color(t_data *data, t_hit_point hit_point, t_sphere *sphere)
{
//	float	facing_ratio;
	float	inten;
	t_vect	light_dir;

	light_dir = sous_vectors(data->lights->coord, hit_point.point);
	inten = data->albedo / M_PI * data->lights->intensity;
//	facing_ratio = fmax(0.f, (float)mult_vectors(sphere->normal(*sphere, hit_point.point), mult_const_vector(ray.direction, -1)));
	return (mult_const_vector(mult_const_vector(data->lights->color, inten), 
				fmax(0.f, (float)mult_vectors(sphere->normal(*sphere, hit_point.point), light_dir))));
}

t_vect	get_color(t_ray ray, t_data *data, int depth, t_vect prev_color)
{
	t_hit_point	hit_point;
//	t_vect	new_direction;
	t_sphere *ptr;

	hit_point = set_closest_obj(ray, data);
	if (depth > MAX_DEPTH) 
		return (prev_color);
	if (hit_point.type == SPHERE)
	{
		ptr = (t_sphere *)hit_point.obj;
//		new_direction = v_normal_sphere(*ptr, hit_point.point);
		return(a_color(data, hit_point, ptr));
//		return (get_color(new_ray(hit_point.point, new_direction), data,  depth + 1, hit_point.color));
	}
	return (prev_color);
}

t_vect	get_sphere_color(t_hit_point hit_point)
{
	t_sphere *sphere;

	if (!hit_point.obj)
		return ((t_vect){0, 0, 0});
	sphere = (t_sphere *)hit_point.obj;
	return (sphere->color);
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
