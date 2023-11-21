/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:58:09 by eorer             #+#    #+#             */
/*   Updated: 2023/11/21 14:25:23 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static int	ray_throwing(t_data *data, int i, int j, t_colors *color)
{
	t_ray		ray;
	t_colors	r_color;

	ray = cast_ray(data, i, j);
	r_color = ray_color(data, ray);
	if (r_color.red == -1)
		return (-1);
	(*color) = add_colors((*color), r_color);
	return (0);
}

int	draw_scene(t_data *data)
{
	int			i;
	int			j;
	t_colors	color;

	i = 0;
	while (i < data->img_width)
	{
		j = -1;
		while (++j < data->img_height)
		{
			color = new_color(0, 0, 0);
			if (ray_throwing(data, i, j, &color) == -1)
				return (1);
			my_mlx_pixel_put(&data->mlx_img, i, j,
				init_color(0, color.red, color.green, color.blue));
		}
		i++;
	}
	return (0);
}
