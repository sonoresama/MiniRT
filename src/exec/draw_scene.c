/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:58:09 by eorer             #+#    #+#             */
/*   Updated: 2023/10/19 17:22:03 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	draw_scene(t_data *data)
{
	int	i;
	int	j;
	t_pixel	pixel;
	t_ray	ray;
	int	color;

	i = 0;
	j = 0;
	while (i < data->img_width)
	{
		while (j < data->img_height)
		{
			pixel.x = i;
			pixel.y = j;
			ray = cast_ray(data, pixel);
			color = ray_color(data, ray);
			if (color == -1)
				return (-1);
			my_mlx_pixel_put(&data->mlx_img, i, j, color);
			j++;
		}
		i++;
	}
	return (0);
}
