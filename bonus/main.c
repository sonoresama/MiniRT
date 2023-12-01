/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:37:41 by eorer             #+#    #+#             */
/*   Updated: 2023/12/01 14:33:14 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

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

void	print_exit(void)
{
	printf("--------- THANK YOU FOR USING ----------\n");
	printf("---------       MINI RT       ----------\n");
}

void	print_manual(void)
{
	printf("----------------------------------------\n");
	printf("-                                      -\n");
	printf("--------- WELCOME TO MINI RT -----------\n");
	printf("-                                      -\n");
	printf("-            * MOVEMENTS *             -\n");
	printf("-                                      -\n");
	printf("- Press UP arrow to move forward       -\n");
	printf("- Press DOWN arrow to move backward    -\n");
	printf("- Press LEFT arrow to move left        -\n");
	printf("- Press RIGHT arrow to move right      -\n");
	printf("- Press w to move up                   -\n");
	printf("- Press s to move down                 -\n");
	printf("-                                      -\n");
	printf("-             * ROTATION *             -\n");
	printf("-                                      -\n");
	printf("- Press a to look left                 -\n");
	printf("- Press d to look right                -\n");
	printf("-                                      -\n");
	printf("----------------------------------------\n");
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (parsing(&data, argc, argv))
		return (1);
	print_manual();
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
	print_exit();
	return (0);
}
