/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:19:42 by eorer             #+#    #+#             */
/*   Updated: 2023/10/13 14:20:07 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	generate_ray(t_ray *ray, t_data *data, t_pixel pixel)
{
	float	x_norm;
	float	y_norm;
	t_vect	pixel_cam;

	if (!data->img_height)
	{
		printf("Height = 0\n");
		return ;
	}
	x_norm = (pixel.x + 0.5) / data->img_width;
	y_norm = (pixel.y + 0.5) / data->img_height;
		// this is assuming img_width > img_height
	pixel_cam.x = (2 * x_norm - 1) * data->screen.aspect_ratio * tan(rad((data->camera.fov / 2))); 
	pixel_cam.y = (1 - 2 * y_norm) * tan(rad((data->camera.fov / 2))); 
	pixel_cam.z = -1.0;
	ray->origin = data->camera.pos;
	pixel_cam = camera_to_world(data->camera.matrix, &pixel_cam, ray->origin);
	ray->direction = sous_vectors(pixel_cam, ray->origin);
	ft_normalize(&ray->direction);
	return ;
}
