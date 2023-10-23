/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:18 by eorer             #+#    #+#             */
/*   Updated: 2023/10/23 18:16:44 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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
		color = get_form_color(data, hit_point);
		free(hit_point);
		return(init_color(0, color.red, color.green, color.blue));
	}
}

//t_colors	get_form_color(t_hit *hit_point, t_ray ray)
//{
//	t_sphere	*sphere;
//
//	(void)ray;
//	if (hit_point->type == SPHERE)
//	{
//		sphere = hit_point->obj;
//		return(sphere->colors);
//	}
//	return((t_colors){0,0,0});
//}

