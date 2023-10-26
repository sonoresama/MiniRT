/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:59:15 by eorer             #+#    #+#             */
/*   Updated: 2023/10/18 17:06:51 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vect	get_sphere_color(t_hit_point hit_point);
t_vect	ray_color(t_ray ray, t_data *data);

t_vect	a_color(t_data *data, t_hit_point hit_point, t_sphere *sphere)
{
	float	facing_ratio;
	float	inten;
	t_vect	light_dir;

	light_dir = sous_vectors(hit_point.point, data->camera.pos);
	//light_dir = sous_vectors(data->lights->coord, hit_point.point);
	inten = data->albedo / M_PI * data->lights->intensity;
	facing_ratio = fmax(0.f, (float)mult_vectors(sphere->normal(*sphere, hit_point.point), mult(light_dir, -1)));
	return (hit_point.color);
	return (mult(data->lights->color, facing_ratio));
//	return (mult(mult(data->lights->color, inten), 
//				fmax(0.f, (float)mult_vectors(sphere->normal(*sphere, hit_point.point), light_dir))));
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
	return (new_vector(200, 0, 155));
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
