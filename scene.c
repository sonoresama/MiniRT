/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:29:27 by eorer             #+#    #+#             */
/*   Updated: 2023/10/16 13:59:05 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//void	set_closest_obj(t_data *data)
//{
//
//}

void	draw_scene(t_data *data)
{
	int	i;
	int	j;
	t_ray	ray;
	float t;
	int	color;

	i = 0;
	j = 0;
	while (i < data->img_width)
	{
		while (j < data->img_height)
		{
			generate_ray(&ray, data, (t_pixel){i, j});
			t = is_hiting_sphere(ray, *data->sphere);
			data->hit_point = add_vectors(ray.origin, mult_const_vector(ray.direction, t));
			color = get_color(data);
			if (t != -1)
				my_mlx_pixel_put(&data->mlx_img, i, j, color);
			else
				my_mlx_pixel_put(&data->mlx_img, i, j, 0);
			j++;
		}
		j = 0;
		i++;
	}
	return ;
}
