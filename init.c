/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:19:28 by eorer             #+#    #+#             */
/*   Updated: 2023/10/16 13:25:34 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_sphere*	init_sphere(void);

int	init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "MINI");
	if (!data->win)
		return (1);
	init_img(&data->mlx_img, &data->mlx, WIDTH, HEIGHT);
	if (!data->mlx_img.img || !data->mlx_img.addr)
		return (1);
	data->img_width = WIDTH;
	data->img_height = HEIGHT;
	data->camera.pos.x = 0;
	data->camera.pos.y = 0;
	data->camera.pos.z = 0;
	data->camera.look.x = 0;
	data->camera.look.y = 0;
	data->camera.look.z = -1;
	data->camera.fov = 90;
	data->screen.focal_length = 1.0;
	data->screen.width = 4.0;
	data->screen.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	data->screen.height = data->screen.width / data->screen.aspect_ratio;
	data->sphere = init_sphere();
	return (0);
}

t_sphere*	init_sphere(void)
{
	t_sphere *sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->radius = 10;
	sphere->center.x = 0;
	sphere->center.y = 0;
	sphere->center.z = -60;
	sphere->color.x = 255;
	sphere->color.y = 255;
	sphere->color.z = 155;
	sphere->next = NULL;
	return (sphere);
}
