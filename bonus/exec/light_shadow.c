/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:41:46 by bastien           #+#    #+#             */
/*   Updated: 2023/11/29 16:22:20 by eorer            ###   ########.fr       */
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
			if ((*t) > 0.001 && (*t) < ft_norm(l_direction) + 0.001)
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
		if ((*t) > 0.001 && (*t) < ft_norm(l_direction) + 0.001)
			return (0);
		plan = plan->next;
	}
	return (1);
}

int	get_form_colors_triangle(t_triangle *triangle, t_hit *hit_point,
	t_vect l_direction)
{
	t_hit	tmp;

	while (triangle)
	{
		ft_bzero(&tmp, sizeof(t_hit));
		if (triangle == hit_point->obj)
		{
			triangle = triangle->next;
			continue ;
		}
		is_hiting_triangle(new_ray(hit_point->point,
				ft_normalize(l_direction)), triangle, &tmp);
		if (tmp.time > 0.001 && tmp.time < ft_norm(l_direction) + 0.001)
			return (0);
		triangle = triangle->next;
	}
	return (1);
}

int	get_form_colors_cyl(float *t, t_cylinder *cylinder, t_hit *hit_point,
		t_vect l_direction)
{
	t_hit	*tmp;

	tmp = ft_calloc(sizeof(t_hit), 1);
	if (!tmp)
		return (0);
	while (cylinder)
	{
		if (cylinder == hit_point->obj)
		{
			cylinder = cylinder->next;
			continue ;
		}
		(*t) = is_hiting_cylinder(new_ray(hit_point->point,
					ft_normalize(l_direction)), cylinder, tmp);
		if ((*t) > 0.001 && (*t) < ft_norm(l_direction) + 0.001)
		{
			free(tmp);
			return (0);
		}
		cylinder = cylinder->next;
	}
	free(tmp);
	return (1);
}

int	light_shadow(t_data *data, t_hit *hit_point, t_vect l_direction)
{
	float		t;
	t_ray		shadow_ray;

	shadow_ray.origin = hit_point->point;
	shadow_ray.direction = hit_point->point.xyz
		- data->scene->light->pos.xyz;
	shadow_ray.direction = ft_normalize(shadow_ray.direction);
	shadow_ray.origin = intersection(shadow_ray, 0.001);
	if (!get_form_colors_sphere(&t, data->scene->sphere,
			hit_point, l_direction))
		return (0);
	if (!get_form_colors_plan(&t, data->scene->plan,
			hit_point, l_direction))
		return (0);
	if (!get_form_colors_cyl(&t, data->scene->cylinder,
			hit_point, l_direction))
		return (0);
	if (!get_form_colors_triangle(data->scene->triangle,
			hit_point, l_direction))
		return (0);
	return (1);
}
