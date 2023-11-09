/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:46 by bastien           #+#    #+#             */
/*   Updated: 2023/11/09 12:23:54 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	get_form_colors_sphere(float *t, t_sphere *sphere, t_hit *hit_point,
	t_vect l_direction)
{
	while (sphere)
	{
		if (sphere != hit_point->obj)
		{
			(*t) = is_hiting_sphere(new_ray(hit_point->point,
						ft_normalize(l_direction)), sphere);
			if ((*t) > 0.01 && (*t) < ft_norm(l_direction) + 0.01)
				return (0);
		}
		sphere = sphere->next;
	}
	return (1);
}

int	get_form_colors_plan(float *t, t_plan *plan, t_hit *hit_point,
	t_vect l_direction)
{
	while (plan)
	{
		if (plan == hit_point->obj)
		{
			plan = plan->next;
			continue ;
		}
		(*t) = is_hiting_plan(new_ray(hit_point->point,
					ft_normalize(l_direction)), plan);
		if ((*t) > 0.01 && (*t) < ft_norm(l_direction) + 0.01)
			return (0);
		plan = plan->next;
	}
	return (1);
}

int	light_shadow(t_data *data, t_hit *hit_point, t_vect l_direction)
{
	float		t;
	t_ray		shadow_ray;

	shadow_ray.origin = hit_point->point;
	shadow_ray.direction = sous_vectors(hit_point->point,
			data->scene->light->pos);
	shadow_ray.direction = ft_normalize(shadow_ray.direction);
	shadow_ray.origin = intersection(shadow_ray, 0.01);
	if (!get_form_colors_sphere(&t, data->scene->sphere,
			hit_point, l_direction))
		return (0);
	if (!get_form_colors_plan(&t, data->scene->plan, hit_point, l_direction))
		return (0);
	return (1);
}
