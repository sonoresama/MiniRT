/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_form_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:18 by eorer             #+#    #+#             */
/*   Updated: 2023/11/09 12:18:46 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	is_hiting_sphere(t_ray ray, t_sphere *sphere);
int	light_shadow(t_data *data, t_hit *hit_point, t_vect l_direction);
t_vect	ft_atmos_intensity(t_atmos *atmos, t_hit *hit_point);
t_vect	ft_diffuse(t_light *light, t_vect l_direction, t_hit *hit_point, t_data *data);
t_vect	ft_specular(t_vect l_direction, t_hit *hit_point, t_ray ray, t_data *data);

t_vect	ft_atmos_intensity(t_atmos *atmos, t_hit *hit_point)
{
	t_vect	result;

	result.x = atmos->ratio * (atmos->colors.red + hit_point->color.red) / 2;
	result.y = atmos->ratio * (atmos->colors.green + hit_point->color.green) / 2;
	result.z = atmos->ratio * (atmos->colors.blue + hit_point->color.blue) / 2;
	return (result);
}

t_vect	ft_diffuse(t_light *light, t_vect l_direction, t_hit *hit_point, t_data *data)
{
	t_vect intensity;
	t_vect	result;

	intensity.x = (light->ratio * light->colors.red) / (4 * M_PI * ft_norm(l_direction));
	intensity.y = (light->ratio * light->colors.green) / (4 * M_PI * ft_norm(l_direction));
	intensity.z = (light->ratio * light->colors.blue) / (4 * M_PI * ft_norm(l_direction));
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

t_vect	ft_specular(t_vect l_direction, t_hit *hit_point,
	t_ray ray, t_data *data)
{
	t_vect	reflect;
	float	prod;
	t_vect	color;
	t_vect	l_ratio;

	l_ratio = ft_light_intensity(data->scene->light, ft_norm(l_direction));
	l_direction = ft_normalize(l_direction);
	reflect = sous_vectors(mult(hit_point->normal, 2
				* dot(l_direction, hit_point->normal)), l_direction);
	prod = dot(ft_normalize(reflect), mult(ray.direction, -1));
	if (prod < 0)
		return (new_vector(0, 0, 0));
	color.x = fmin(255, hit_point->color.red * l_ratio.x * pow(prod, N));
	color.y = fmin(255, hit_point->color.green * l_ratio.y * pow(prod, N));
	color.z = fmin(255, hit_point->color.blue * l_ratio.z * pow(prod, N));
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
	while (light)
	{
		l_direction = sous_vectors(light->pos, hit_point->point);
		shadow = light_shadow(data, hit_point, l_direction);
		a_intensity = ft_atmos_intensity(data->scene->atmos, hit_point);
		diffuse = add_vectors(diffuse, mult(ft_diffuse(light, l_direction,
					hit_point, data), shadow));
		specular = add_vectors(specular, mult(ft_specular(l_direction, hit_point,
					ray, data), shadow));
		light = light->next;
	}
	return (new_color(fmin(255, (DIFFUSE * diffuse.x + SPECULAR * specular.x)
				* shadow * hit_point->color.red + a_intensity.x), fmin(255,
				(DIFFUSE * diffuse.y + SPECULAR * specular.y) * shadow
				* hit_point->color.green + a_intensity.y), fmin(255, (DIFFUSE
					* diffuse.z + SPECULAR * specular.z) * shadow
				* hit_point->color.blue + a_intensity.z)));
}
