/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:35:17 by bastien           #+#    #+#             */
/*   Updated: 2023/11/21 15:17:18 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	ft_init_data(t_data *data, t_scene *scene)
{
	t_win_list	*tmp;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (printf("%s", MLX_ERR), 1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
		return (mlx_destroy_display(data->mlx), free(data->mlx),
			printf("%s", MLX_ERR), 1);
	init_img(&data->mlx_img, &data->mlx, WIDTH, HEIGHT);
	if (!data->mlx_img.img || !data->mlx_img.addr)
	{
		tmp = data->win;
		return (mlx_destroy_display(data->mlx), free(tmp->gc), free(data->win),
			free(data->mlx), printf("%s", MLX_ERR), 1);
	}
	data->scene = scene;
	data->img_width = WIDTH;
	data->img_height = HEIGHT;
	data->screen.focal_length = 1.0;
	data->screen.width = 4.0;
	data->screen.aspect_ratio = (double)WIDTH / (double)HEIGHT;
	data->screen.height = data->screen.width / data->screen.aspect_ratio;
	return (data->error = 0, data->scene->albedo = 0.18, 0);
}
