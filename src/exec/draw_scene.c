/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:58:09 by eorer             #+#    #+#             */
/*   Updated: 2023/11/08 17:40:28 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	get_sampled_color(t_colors color)
{
	int	r;
	int	g;
	int	b;

	r = color.red / SAMPLES_PER_PIXEL;
	g = color.green / SAMPLES_PER_PIXEL;
	b = color.blue / SAMPLES_PER_PIXEL;
	return (init_color(0, r, g, b));
}

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
	int			s;
	t_colors	color;

	i = 0;
	while (i < data->img_width)
	{
		j = 0;
		while (j < data->img_height)
		{
			s = 0;
			color = new_color(0, 0, 0);
			while (s < SAMPLES_PER_PIXEL)
			{
				if (ray_throwing(data, i, j, &color) == -1)
					return (-1);
				s++;
			}
			my_mlx_pixel_put(&data->mlx_img, i, j, get_sampled_color(color));
			j++;
		}
		i++;
	}
	return (0);
}
