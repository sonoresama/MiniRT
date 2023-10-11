/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:37:41 by eorer             #+#    #+#             */
/*   Updated: 2023/09/26 11:45:24 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

#define WIDTH 800
#define HEIGHT 450 

int	keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	return (0);
}

int	render(void *ptr)
{
	(void)ptr;
	return (0);
}

void	print_mat_x3(double matrix[3][3])
{
	int	i = 0;
	int	j = 0;

	while (i < 3)
	{
		while (j < 3)
		{
			printf("%f ", matrix[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}

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
	data->camera.pos.y = 10;
	data->camera.pos.z = 0;
	data->camera.look.x = 0;
	data->camera.look.y = 0;
	data->camera.look.z = -1;
	data->camera.fov = 90;
	data->screen.focal_length = 1.0;
	data->screen.width = 4.0;
	data->screen.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	data->screen.height = data->screen.width / data->screen.aspect_ratio;
	return (0);
}

void	init_sphere(t_sphere *sphere)
{
	sphere->radius = 10;
	sphere->center.x = 0;
	sphere->center.y = 0;
	sphere->center.z = -20;
	sphere->color.x = 255;
	sphere->color.y = 255;
	sphere->color.z = 155;
}

void	print_vect(t_vect vect)
{
	printf("(%f %f %f)\n", vect.x, vect.y, vect.z);
}

int	main(void)
{
	t_data		data;
	t_sphere	sphere;

	if (init_data(&data))
		return (1);
	init_sphere(&sphere);
	draw_sphere(&data, &sphere);
	mlx_put_image_to_window(data.mlx, data.win, data.mlx_img.img, 0, 0);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &keypress, &data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, data.mlx_img.img);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
