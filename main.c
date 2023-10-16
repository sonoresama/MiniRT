/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:37:41 by eorer             #+#    #+#             */
/*   Updated: 2023/10/16 13:24:32 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handle_key(int keycode, t_data *data)
{
	if (keycode == XK_Left)
		data->camera.look.x -= 0.1;
	else if (keycode == XK_Right)
		data->camera.look.x += 0.1;
	else if (keycode == XK_Up)
		data->camera.look.y -= 0.1;
	else if (keycode == XK_Down)
		data->camera.look.y += 0.1;
	generate_rot_matrix(data);
}

int	keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		return (0);
	}
	else
		handle_key(keycode, data);
	draw_scene(data);
	mlx_put_image_to_window(data->mlx, data->win, data->mlx_img.img, 0, 0);
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

int	main(void)
{
	t_data		data;

	if (init_data(&data))
		return (1);
	generate_rot_matrix(&data);
	draw_scene(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.mlx_img.img, 0, 0);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &keypress, &data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, data.mlx_img.img);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
