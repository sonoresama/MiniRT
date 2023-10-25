/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_form_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:18 by eorer             #+#    #+#             */
/*   Updated: 2023/10/25 17:19:41 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	is_hiting_sphere(t_ray ray, t_sphere *sphere);

t_colors	get_form_color(t_data *data, t_hit *hit_point)
{
	t_colors	color;
	t_vect	l_direction;
	float	facing_ratio;
	int	shadow;
	t_hit	*hit;

	hit = ft_calloc(sizeof(t_hit), 1);
	l_direction = sous_vectors(data->scene->light->pos, hit_point->point);
//	l_direction = ft_normalize(l_direction);
	color = hit_point->color;
	shadow = 0;
	get_closest_sphere(new_ray(hit_point->point, ft_normalize(l_direction)), data->scene->sphere, hit);
	if (!hit->obj || hit->obj == hit_point->obj)
		shadow = 1;
	if (hit_point->type == PLAN)
	{
		if (shadow == 1)
			return (color);
		else
			return (new_color(0, 0, 0));
	}
	facing_ratio = shadow * data->scene->albedo / M_PI * data->scene->light->ratio 
			* fmax(0.0, dot(hit_point->normal, l_direction));
//	color.red = facing_ratio * color.red;
//	color.green = facing_ratio * color.green;
//	color.blue = facing_ratio * color.blue;
	color.red = fmin(255, facing_ratio * color.red);
	color.green = fmin(255, facing_ratio * color.green);
	color.blue = fmin(255, facing_ratio * color.blue);
	free(hit);
	return (color);
}
