/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:29:27 by eorer             #+#    #+#             */
/*   Updated: 2023/09/26 11:42:03 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_hiting_sphere(t_ray ray, t_sphere sphere)
{
	double	a;
	double	b;
	double	c;

	a = mult_vectors(ray.direction, ray.direction);
	b = mult_vectors(mult_const_vector(ray.direction, 2), sous_vectors(ray.origin, sphere.center));
	c = mult_vectors(sous_vectors(ray.origin, sphere.center), sous_vectors(ray.origin, sphere.center)) - pow(sphere.radius, 2);
	if (pow(b, 2) - 4 * a * c >= 0)
		return (1);
	return (0);
}

void	draw_sphere(t_data *data, t_sphere *sphere)
{
	int	i;
	int	j;
	t_ray	ray;

	i = 0;
	j = 0;
	while (i < data->img_width)
	{
		while (j < data->img_height)
		{
			generate_ray(&ray, data, (t_pixel){i, j});
			if (is_hiting_sphere(ray, *sphere))
				my_mlx_pixel_put(&data->mlx_img, i, j, init_color(0, 255, 255, 150));
			else
				my_mlx_pixel_put(&data->mlx_img, i, j, 0);
			j++;
		}
		j = 0;
		i++;
	}
	return ;
}

void	generate_rot_matrix(t_data *data)
{
	t_vect	forward;
	t_vect	right;
	t_vect	up;
	t_vect	tmp;

	tmp = new_vector(0, 1, 0);
	forward = data->camera.look;
	ft_normalize(&forward);
	right = cross_product(tmp, forward);
	up = cross_product(forward, right);
	data->camera.matrix[0][0] = right.x;
	data->camera.matrix[0][1] = right.y;
	data->camera.matrix[0][2] = right.z;
	data->camera.matrix[1][0] = up.x;
	data->camera.matrix[1][1] = up.y;
	data->camera.matrix[1][2] = up.z;
	data->camera.matrix[2][0] = forward.x;
	data->camera.matrix[2][1] = forward.y;
	data->camera.matrix[2][2] = forward.z;
}

t_vect	camera_to_world(double matrix[3][3], t_vect *vector)
{
	t_vect	result;
	result.x = vector->x * matrix[0][0] + vector->y * matrix[1][0] + vector->z * matrix[2][0];
	result.y = vector->x * matrix[0][1] + vector->y * matrix[1][1] + vector->z * matrix[2][1];
	result.z = vector->x * matrix[0][2] + vector->y * matrix[1][2] + vector->z * matrix[2][2];
	return (result);
}

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
	generate_rot_matrix(data);
	ray->direction = camera_to_world(data->camera.matrix, &pixel_cam);
//	print_vect(pixel_cam);
//	pixel_cam = rotate_cam(data->fov / 2, 1, pixel_cam);
//	pixel_cam = rotate_cam(data->fov / 2, 2, pixel_cam);
//	pixel_cam = rotate_cam(data->fov / 2, 3, pixel_cam);
//	pixel_cam = add_vectors(pixel_cam, data->camera.pos);
//	print_vect(pixel_cam);
//	ray->direction = sous_vectors(pixel_cam, ray->origin);
	ft_normalize(&ray->direction);
	return ;
}
