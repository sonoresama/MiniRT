/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:29:27 by eorer             #+#    #+#             */
/*   Updated: 2023/10/13 15:14:08 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	draw_scene(t_data *data)
{
	int	i;
	int	j;
	t_ray	ray;
	float t;
//	t_vect	hit_point;
//	t_vect	*ptr;

	i = 0;
	j = 0;
	while (i < data->img_width)
	{
		while (j < data->img_height)
		{
			ptr = &hit_point;
			generate_ray(&ray, data, (t_pixel){i, j});
			is_hiting_sphere(ray, data->sphere, &ptr);
			if (ptr)
				my_mlx_pixel_put(&data->mlx_img, i, j, init_color(0, 255, 255, 150));
			else
				my_mlx_pixel_put(&data->mlx_img, i, j, 0);
			j++;
		}
		j = 0;
		i++;
	}
	return ;
}
