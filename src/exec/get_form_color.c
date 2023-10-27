/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_form_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:18 by eorer             #+#    #+#             */
/*   Updated: 2023/10/27 19:32:35 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

float	is_hiting_sphere(t_ray ray, t_sphere *sphere);
int	light_shadow(t_data *data, t_hit *hit_point, t_vect l_direction);
t_vect	ft_atmos_intensity(t_atmos *atmos);
t_vect	ft_light_intensity(t_light *light, float distance);

t_colors	get_form_color(t_data *data, t_hit *hit_point)
{
	t_colors	color;
	t_light	*light;
	t_vect	l_direction;
	t_vect	l_intensity;
	t_vect	a_intensity;
	t_vect	shading_ratio;
	int	shadow;

	light = data->scene->light;
	color = new_color(0, 0, 0);
	while (light)
	{
		l_direction = sous_vectors(light->pos, hit_point->point);
		if (hit_point->type == PLAN)
		{
			if (dot(hit_point->normal, ft_normalize(l_direction)) < 0)
				hit_point->normal = mult(hit_point->normal, -1);
		}
		shadow = light_shadow(data, hit_point, l_direction);
		l_intensity = ft_light_intensity(light, ft_norm(l_direction));
		a_intensity = ft_atmos_intensity(data->scene->atmos);
		shading_ratio = mult(l_intensity, shadow * data->scene->albedo / M_PI  
				* fmax(0.0, dot(hit_point->normal, l_direction)));
		color.red += fmin(255, shading_ratio.x * hit_point->color.red + a_intensity.x);	
		color.green += fmin(255, shading_ratio.y * hit_point->color.green + a_intensity.y);
		color.blue += fmin(255, shading_ratio.z * hit_point->color.blue + a_intensity.z);
		light = light->next;
	}
	return (color);
}

int	light_shadow(t_data *data, t_hit *hit_point, t_vect l_direction)
{
	float	t;
	t_sphere	*sphere;
	t_plan	*plan;

 	sphere = data->scene->sphere;
	while(sphere)
	{
		if (sphere != hit_point->obj)
		{
			t = is_hiting_sphere(new_ray(hit_point->point, ft_normalize(l_direction)), sphere);
			if (t > 0.01 && t < ft_norm(l_direction))
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
		if (t > 0.01 && t < ft_norm(l_direction))
			return (0);
		plan = plan->next;
	}
	return (1);
}

//int	light_shadow(t_data *data, t_hit *hit_point, t_vect l_direction)
//{
//	t_hit *hit;
//
//	hit = ft_calloc(sizeof(t_hit), 1);
//	if (!hit)
//		return (data->error = MALLOC_ERR, -1);
//	get_closest_sphere(new_ray(hit_point->point, l_direction), data->scene->sphere, hit);
//	if (!hit->obj || hit->obj == hit_point->obj)
//		return (free(hit), 1);
////	if (hit->obj && hit->obj != hit_point->obj)// || hit->time > ft_norm(l_direction))
////		return (free(hit), 0);
////	ft_bzero(hit, sizeof(t_hit));
////	get_closest_plan(new_ray(hit_point->point, l_direction), data->scene->plan, hit);
////	if (hit->obj && hit->obj != hit_point->obj)// || hit->time > ft_norm(l_direction))
////		return (free(hit), 0);
//	else
//	{
//		if (hit->obj && hit_point->type == SPHERE)
//			printf("1st sphere : %p      hit sphere : %p    hit point : %p\n", data->scene->sphere, hit->obj, hit_point->obj);
//		return (free(hit), 0);
//	}
//}

t_vect	ft_atmos_intensity(t_atmos *atmos)
{
	t_vect	result;

	result.x = atmos->ratio * atmos->colors.red;
	result.y = atmos->ratio * atmos->colors.green;
	result.z = atmos->ratio * atmos->colors.blue;
	return (result);
}

t_vect	ft_light_intensity(t_light *light, float distance)
{
	t_vect intensity;

	intensity.x = (light->ratio * light->colors.red) / (4 * M_PI * distance);
	intensity.y = (light->ratio * light->colors.green) / (4 * M_PI * distance);
	intensity.z = (light->ratio * light->colors.blue) / (4 * M_PI * distance);
	return (intensity);
}
