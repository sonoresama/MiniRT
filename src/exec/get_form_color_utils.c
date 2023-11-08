/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_form_color_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:20:35 by bastien           #+#    #+#             */
/*   Updated: 2023/11/08 16:33:45 by bastien          ###   ########.fr       */
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

	intensity.x = (light->ratio * light->colors.red)
		/ (4 * M_PI * ft_norm(l_direction));
	intensity.y = (light->ratio * light->colors.green)
		/ (4 * M_PI * ft_norm(l_direction));
	intensity.z = (light->ratio * light->colors.blue)
		/ (4 * M_PI * ft_norm(l_direction));
	result = mult(intensity, data->scene->albedo / M_PI
			* fmax(0.0, dot(hit_point->normal, l_direction)));
	return (result);
}

t_vect	ft_light_intensity(t_light *light, float distance)
{
	t_vect	intensity;

	intensity.x = (light->ratio * light->colors.red) / (4 * M_PI * distance);
	intensity.y = (light->ratio * light->colors.green) / (4 * M_PI * distance);
	intensity.z = (light->ratio * light->colors.blue) / (4 * M_PI * distance);
	return (intensity);
}
