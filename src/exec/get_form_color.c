/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_form_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:18 by eorer             #+#    #+#             */
/*   Updated: 2023/11/03 18:53:54 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

#define SPECULAR 0.003
#define DIFFUSE  0.997
#define N 50

float	is_hiting_sphere(t_ray ray, t_sphere *sphere);
int	light_shadow(t_data *data, t_hit *hit_point, t_vect l_direction);
t_vect	ft_atmos_intensity(t_atmos *atmos, t_hit *hit_point);
t_vect	ft_diffuse(t_light *light, t_vect l_direction, t_hit *hit_point, t_data *data);
t_vect	ft_specular(t_vect l_direction, t_hit *hit_point, t_ray ray, t_data *data);

t_colors	get_form_color(t_data *data, t_hit *hit_point, t_ray ray)
{
	t_colors	color;
	t_light	*light;
	t_vect	l_direction;
	t_vect	a_intensity;
	t_vect	specular;
	t_vect	diffuse;
	int	shadow;

	light = data->scene->light;
	color = new_color(0, 0, 0);
	diffuse = new_vector(0, 0, 0);
	specular = new_vector(0, 0, 0);
	while (light)
	{
		l_direction = sous_vectors(light->pos, hit_point->point);
		shadow = light_shadow(data, hit_point, l_direction);
		a_intensity = ft_atmos_intensity(data->scene->atmos, hit_point);
		diffuse = add_vectors(diffuse, ft_diffuse(light, l_direction, hit_point, data));
		specular = add_vectors(specular, ft_specular(l_direction, hit_point, ray, data));
		light = light->next;
	}
	color.red = fmin(255, (DIFFUSE * diffuse.x + SPECULAR * specular.x) * shadow * hit_point->color.red + a_intensity.x);	
	color.green = fmin(255, (DIFFUSE * diffuse.y + SPECULAR * specular.y) * shadow * hit_point->color.green + a_intensity.y);
	color.blue = fmin(255, (DIFFUSE * diffuse.z + SPECULAR * specular.z) * shadow * hit_point->color.blue + a_intensity.z);
	return (color);
}

int	light_shadow(t_data *data, t_hit *hit_point, t_vect l_direction)
{
	float	t;
	t_sphere	*sphere;
	t_plan	*plan;
	t_ray	shadow_ray;

	shadow_ray.origin = hit_point->point;
	shadow_ray.direction = sous_vectors(hit_point->point, data->scene->light->pos);
	shadow_ray.direction = ft_normalize(shadow_ray.direction);
	shadow_ray.origin = intersection(shadow_ray, 0.01);
 	sphere = data->scene->sphere;
	while(sphere)
	{
		if (sphere != hit_point->obj)
		{
			t = is_hiting_sphere(new_ray(hit_point->point, ft_normalize(l_direction)), sphere);
			if (t > 0.1 && t < ft_norm(l_direction) + 0.01)
				return (0);
		}
		sphere = sphere->next;
	}
	plan = data->scene->plan;
	while(plan)
	{
		if (plan == hit_point->obj)
		{
			plan = plan->next;
			continue;
		}
		t = is_hiting_plan(new_ray(hit_point->point, ft_normalize(l_direction)), plan);
		if (t > 0.1 && t < ft_norm(l_direction) + 0.01)
			return (0);
		plan = plan->next;
	}
	return (1);
}

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

t_vect	ft_specular(t_vect l_direction, t_hit *hit_point, t_ray ray, t_data *data)
{
	t_vect	reflect;
	float	prod;
	t_vect	color;
	t_vect	l_ratio;

	l_ratio = ft_light_intensity(data->scene->light, ft_norm(l_direction));
	l_direction = ft_normalize(l_direction);
	reflect = sous_vectors(mult(hit_point->normal, 2 * dot(l_direction, hit_point->normal)), l_direction);
	prod = dot(ft_normalize(reflect), mult(ray.direction, -1));
	if (prod < 0)
		return (new_vector(0, 0, 0));
	color.x = fmin(255, hit_point->color.red * l_ratio.x * pow(prod, N));
	color.y = fmin(255, hit_point->color.green * l_ratio.y * pow(prod, N));
	color.z = fmin(255, hit_point->color.blue * l_ratio.z * pow(prod, N));
	return (color); 
}
