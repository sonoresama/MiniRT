/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_form_color_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:20:35 by bastien           #+#    #+#             */
/*   Updated: 2023/11/29 13:18:15 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vect	ft_atmos_intensity(t_atmos *atmos, t_hit *hit_point)
{
	t_vect	result;

	result.x = atmos->ratio * (atmos->colors.red + hit_point->color.red) / 2;
	result.y = atmos->ratio * (atmos->colors.green + hit_point->color.green)
		/ 2;
	result.z = atmos->ratio * (atmos->colors.blue + hit_point->color.blue) / 2;
	return (result);
}

t_vect	ft_diffuse(t_light *light, t_vect l_direction,
	t_hit *hit_point, t_data *data)
{
	t_vect	intensity;
	t_vect	result;

	intensity = ft_light_intensity(light, ft_norm(l_direction));
	result = mult(intensity, data->scene->albedo / M_PI
			* fmax(0.0, dot(hit_point->normal, l_direction)));
	return (result);
}

t_vect	ft_light_intensity(t_light *light, float distance)
{
	return ((t_vect)
		{(light->ratio * light->colors.red) / (4 * M_PI * distance),
			(light->ratio * light->colors.green) / (4 * M_PI * distance),
			(light->ratio * light->colors.blue) / (4 * M_PI * distance)});
}

t_vect	ft_specular(t_vect l_direction, t_hit *hit_point,
	t_ray ray, t_data *data)
{
	t_vect	reflect;
	float	prod;
	t_vect	color;
	t_vect	l_ratio;

	l_ratio = ft_light_intensity(data->scene->light, ft_norm(l_direction));
	l_direction = ft_normalize(l_direction);
	reflect = (hit_point->normal.xyz
			* 2 * dot(l_direction, hit_point->normal)) - l_direction.xyz;
	prod = dot(ft_normalize(reflect), ray.direction.xyz * -1);
	if (prod < 0)
		return (new_vector(0, 0, 0));
	color.x = fmin(255, hit_point->color.red * l_ratio.x * pow(prod, N));
	color.y = fmin(255, hit_point->color.green * l_ratio.y * pow(prod, N));
	color.z = fmin(255, hit_point->color.blue * l_ratio.z * pow(prod, N));
	return (color);
}
