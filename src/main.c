/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:37:41 by eorer             #+#    #+#             */
/*   Updated: 2023/11/30 15:35:17 by blerouss         ###   ########.fr       */
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

int	handle_client_message(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	data->win = NULL;
	return (0);
}

int	render(void *ptr)
{
	(void)ptr;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (parsing(&data, argc, argv))
		return (1);
	printf("Done\n");
	mlx_put_image_to_window(data.mlx, data.win, data.mlx_img.img, 0, 0);
	mlx_loop_hook(data.mlx, &render, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &keypress, &data);
	mlx_hook(data.win, ClientMessage, StructureNotifyMask,
		&handle_client_message, &data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, data.mlx_img.img);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	ft_clear_all(data.scene);
	return (0);
}
