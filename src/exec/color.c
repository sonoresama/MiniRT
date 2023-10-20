/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:18 by eorer             #+#    #+#             */
/*   Updated: 2023/10/20 15:27:05 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_colors	get_form_color(t_hit *hit_point);

int	ray_color(t_data *data, t_ray ray)
{
	t_hit	*hit_point;
	t_colors	color;

	hit_point = get_closest_sphere(data, ray);
	if (!hit_point && data->error == MALLOC_ERR)
		return (-1);
	if (!hit_point)
	{
		free(hit_point);
		return (init_color(0, 0, 0, 0));
	}
	else 
	{
		color = get_form_color(hit_point);
		free(hit_point);
		return(init_color(0, color.red, color.green, color.blue));
	}
}

t_colors	get_form_color(t_hit *hit_point)
{
	t_sphere	*sphere;
//	t_plan		*plan;
//	t_cylinder	*cyl;

	if (hit_point->type == SPHERE)
	{
		sphere = hit_point->obj;
		return (sphere->colors);
	}
	return ((t_colors){0, 0, 0});
}
