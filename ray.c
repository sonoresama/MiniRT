/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:19:42 by eorer             #+#    #+#             */
/*   Updated: 2023/10/16 19:25:25 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

float	pixel_sample(void)
{
	float	a;
	float	x;

	if (SAMPLES_PER_PIXEL <= 1)
		return (0);
	a = 1.0;
	x = -0.5 + ((float)rand()/(float)(RAND_MAX)) * a;
	return (x);
}

t_ray	generate_ray(t_data *data, t_pixel pixel)
{
	float	x_norm;
	float	y_norm;
	t_vect	pixel_cam;
	t_ray	ray;

	ray.origin = new_vector(0, 0, 0);
	ray.direction = new_vector(0, 0, 0);
	if (!data->img_height)
	{
		printf("Height = 0\n");
		return (ray);
	}
	x_norm = (pixel.x + 0.5 + pixel_sample()) / data->img_width;
	y_norm = (pixel.y + 0.5 + pixel_sample()) / data->img_height;
		// this is assuming img_width > img_height
	pixel_cam.x = (2 * x_norm - 1) * data->screen.aspect_ratio * tan(rad((data->camera.fov / 2))); 
	pixel_cam.y = (1 - 2 * y_norm) * tan(rad((data->camera.fov / 2))); 
	pixel_cam.z = -1.0;
	ray.origin = data->camera.pos;
	pixel_cam = camera_to_world(data->camera.matrix, &pixel_cam, ray.origin);
	ray.direction = sous_vectors(pixel_cam, ray.origin);
	ft_normalize(&ray.direction);
	return (ray);
}

t_ray	new_ray(t_vect origin, t_vect direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}
