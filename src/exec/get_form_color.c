/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_form_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:18 by eorer             #+#    #+#             */
/*   Updated: 2023/10/23 18:16:50 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_colors	get_form_color(t_data *data, t_hit *hit_point)
{
	t_colors	color;
	t_vect	l_direction;
	float	facing_ratio;
	int	shadow;
	t_hit	*hit;

	l_direction = sous_vectors(hit_point->point, data->scene->light->pos);
	color = hit_point->color;
	shadow = 0;
	hit = get_closest_sphere(data, new_ray(hit_point->point, ft_normalize(l_direction)));
	if (!hit || hit->obj == hit_point->obj)
		shadow = 1;
	facing_ratio = shadow * data->scene->albedo / M_PI * data->scene->light->ratio 
			* fmax(0.0, dot(hit_point->normal, mult_const_vector(l_direction, -1)));
	color.red = fmin(255, facing_ratio * color.red);
	color.green = fmin(255, facing_ratio * color.green);
	color.blue = fmin(255, facing_ratio * color.blue);
	free(hit);
	return (color);
}
