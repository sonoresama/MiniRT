/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:37:41 by eorer             #+#    #+#             */
/*   Updated: 2023/10/19 15:01:06 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		return (0);
	}
	return (0);
}

int	render(void *ptr)
{
	(void)ptr;
	return (0);
}

int	init_data(t_data *data, t_scene *scene)
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
	data->scene = scene;
	data->img_width = WIDTH;
	data->img_height = HEIGHT;
	data->screen.focal_length = 1.0;
	data->screen.width = 4.0;
	data->screen.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	data->screen.height = data->screen.width / data->screen.aspect_ratio;
	data->albedo = 0.18;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_scene		*scene;

	scene = ft_calloc(sizeof(t_scene), 1);
	if (check_file(argc, argv, scene))
		return (ft_clear_all(scene), 1);
	if (init_data(&data, scene))
		return (1);
	mlx_put_image_to_window(data.mlx, data.win, data.mlx_img.img, 0, 0);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, &keypress, &data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, data.mlx_img.img);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	ft_clear_all(scene);
	return (0);
}
