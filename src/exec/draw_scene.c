/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:58:09 by eorer             #+#    #+#             */
/*   Updated: 2023/10/20 15:30:44 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	draw_scene(t_data *data)
{
	int	i;
	int	j;
	t_ray	ray;
	int	color;

	i = 0;
	while (i < data->img_width)
	{
		j = 0;
		while (j < data->img_height)
		{
			ray = cast_ray(data, i, j);
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
