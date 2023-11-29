/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:39 by eorer             #+#    #+#             */
/*   Updated: 2023/11/28 18:16:59 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	pixel_sample(void)
{
	float	a;
	float	x;

	if (SAMPLES_PER_PIXEL <= 1)
		return (0);
	a = 1.0;
	x = -0.5 + ((float)rand() / (float)(RAND_MAX)) * a;
	return (x);
}

t_ray	new_ray(t_vect origin, t_vect direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_ray	cast_ray(t_data *data, int i, int j)
{
	t_vect	pixel_cam;
	t_ray	ray;

	pixel_cam.x = (2 * (i + 0.5 + pixel_sample()) / WIDTH - 1)
		* data->screen.aspect_ratio * data->scene->camera->scale;
	pixel_cam.y = (1 - 2 * (j + 0.5 + pixel_sample())
			/ HEIGHT) * data->scene->camera->scale;
	pixel_cam.z = 1;
	ray = new_ray(data->scene->camera->pos, pixel_cam);
	ray.direction = mult_mat_vect(data->scene->camera->matrix, ray.direction);
	ray.direction = ft_normalize(ray.direction);
	return (ray);
}
