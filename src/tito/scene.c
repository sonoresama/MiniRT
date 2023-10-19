/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:29:27 by eorer             #+#    #+#             */
/*   Updated: 2023/10/18 16:11:39 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	set_bg(t_data *data)
{
	data->hit_point.type = BACKGROUND;
	data->hit_point.t = 0;
	data->hit_point.obj = NULL;
}

t_hit_point	set_closest_obj(t_ray ray, t_data *data)
{
	t_hit_point	hit_point;
	float	t;

	t = get_closest_sphere(ray, data, &hit_point);
	if (t == 0)
	{
		hit_point.point = new_vector(0, 0, 0);
		hit_point.type = BACKGROUND;
		hit_point.t = 0;
		hit_point.obj = NULL;
		hit_point.color = new_vector(0, 0, 0);
		return (hit_point);
	}
	hit_point.point = add_vectors(ray.origin, mult_const_vector(ray.direction, t));
	hit_point.type = SPHERE;
	hit_point.t = t;
	hit_point.color = get_sphere_color(hit_point);
	// get_closest_sphere set dej *obj et type
	return (hit_point);
}

void	draw_scene(t_data *data)
{
	int	i;
	int	j;
	int	s;
	t_ray	ray;
	t_vect	color;

	i = 0;
	j = 0;
	while (i < data->img_width)
	{
		while (j < data->img_height)
		{
			color = new_vector(0, 0, 0);
			s = 0;

			{
				ray = generate_ray(data, (t_pixel){i, j});
				color = add_vectors(color, get_color(ray, data, 0, (t_vect){0, 0, 0}));
				s++;
			}
			my_mlx_pixel_put(&data->mlx_img, i, j, get_sampled_color(color));
			j++;
		}
		j = 0;
		i++;
	}
	return ;
}
