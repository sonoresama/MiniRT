/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_form_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:18 by eorer             #+#    #+#             */
/*   Updated: 2023/11/30 18:59:35 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_colors	send_color(t_vect diffuse, t_vect specular, t_vect a_intensity,
		t_hit *hit_point)
{
	t_colors	color;

	color.red = fmin(255, (DIFFUSE * diffuse.x + SPECULAR * specular.x)
			* hit_point->color.red + a_intensity.x);
	color.green = fmin(255, (DIFFUSE * diffuse.y + SPECULAR * specular.y)
			* hit_point->color.green + a_intensity.y);
	color.blue = fmin(255, (DIFFUSE * diffuse.z + SPECULAR * specular.z)
			* hit_point->color.blue + a_intensity.z);
	return (color);
}

t_colors	get_form_color(t_data *data, t_hit *hit_point, t_ray ray,
	t_light *light)
{
	t_vect		l_direction;
	t_vect		a_intensity;
	t_vect		specular;
	t_vect		diffuse;
	int			shadow;

	diffuse = new_vector(0, 0, 0);
	specular = new_vector(0, 0, 0);
	a_intensity = ft_atmos_intensity(data->scene->atmos, hit_point);
	while (light)
	{
		l_direction = light->pos.xyz - hit_point->point.xyz;
		shadow = light_shadow(data, hit_point, l_direction);
		diffuse = add_vectors(diffuse, mult(ft_diffuse(light, l_direction,
						hit_point, data), shadow));
		specular = add_vectors(specular, mult(ft_specular(l_direction,
						hit_point, ray, data), shadow));
		light = light->next;
	}
	return (send_color(diffuse, specular, a_intensity, hit_point));
}
