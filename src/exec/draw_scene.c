/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:58:09 by eorer             #+#    #+#             */
/*   Updated: 2023/10/24 14:05:45 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	get_sampled_color(t_colors color);

int	draw_scene(t_data *data)
{
	int	i;
	int	j;
	int	s;
	t_ray	ray;
	t_colors	color;

	i = 0;
	color = new_color(0, 0, 0);
	while (i < data->img_width)
	{
		j = 0;
		while (j < data->img_height)
		{
			s = 0;
			while (s < SAMPLES_PER_PIXEL)
			{
				ray = cast_ray(data, i, j);
				color = add_colors(color, ray_color(data, ray));
		//		if (color == -1)
		//			return (-1);
				s++;
			}
			my_mlx_pixel_put(&data->mlx_img, i, j, get_sampled_color(color));
			j++;
		}
		i++;
	}
	return (0);
}

int	get_sampled_color(t_colors color)
{
	t_colors	result;

	result.red = color.red / SAMPLES_PER_PIXEL;
	result.green = color.green / SAMPLES_PER_PIXEL;
	result.blue = color.blue / SAMPLES_PER_PIXEL;
	return (init_color(0, result.red, result.green, result.blue));
}
