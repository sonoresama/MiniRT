/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:39 by eorer             #+#    #+#             */
/*   Updated: 2023/10/19 17:30:04 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_ray	new_ray(t_vect origin, t_vect direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_ray	cast_ray(t_data *data, t_pixel pixel)
{
	t_vect	pixel_cam;
	float	scale;
	t_ray	ray;

	scale = tan(rad(data->scene->camera->fov * 0.5));
	pixel_cam.x = (2 * (pixel.x + 0.5) / data->img_width - 1) * data->screen.aspect_ratio * scale;
	pixel_cam.y = (1 - 2 * (pixel.y + 0.5) / data->img_height) * scale;
	pixel_cam.z = -1;
	ray = new_ray(data->scene->camera->pos, sous_vectors(pixel_cam, data->scene->camera->pos));
	ft_normalize(&ray.direction);
	return (ray);
}
