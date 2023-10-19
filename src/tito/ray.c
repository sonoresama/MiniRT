/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:19:42 by eorer             #+#    #+#             */
/*   Updated: 2023/10/18 17:05:18 by eorer            ###   ########.fr       */
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
	x = -0.5 + ((float)rand()/(float)(RAND_MAX)) * a;
	return (x);
}

t_ray	generate_ray(t_data *data, t_pixel pixel)
{
	t_vect	pixel_cam;
	t_ray	ray;
	float	scale;

	scale = tan(rad(data->camera.fov / 2));
	if (!data->img_height)
	{
		printf("Height = 0\n");
		return (new_ray(new_vector(0, 0, 0), new_vector(0, 0, 0)));
	}
	pixel_cam.x = (2 * (pixel.x + 0.5 + pixel_sample()) / WIDTH - 1) * data->screen.aspect_ratio * scale;
	pixel_cam.y = (1 - 2 * (pixel.y + 0.5 + pixel_sample()) / HEIGHT) * scale;
	pixel_cam.z = -1.0;
	ray = new_ray(data->camera.pos, sous_vectors(pixel_cam, data->camera.pos));
//	pixel_cam = camera_to_world(data->camera.matrix, &pixel_cam, ray.origin);
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
