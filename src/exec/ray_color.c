/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:19:25 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/24 13:54:39 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_colors	ray_color(t_data *data, t_ray ray)
{
	t_hit	*hit_point;
	t_colors	color;

	hit_point = ft_calloc(sizeof(t_hit), 1);
	if (!hit_point)
		return (printf("%s", MAL_ERR), data->error = MALLOC_ERR, 0);
	get_closest_sphere(ray, data->scene->sphere, hit_point);
	get_closest_plan(ray, data->scene->plan, hit_point);
//	get_closest_cylinder(ray, data->scene->cylinder, hit_point);
	if (!hit_point->obj)
		return (free(hit_point), init_color(0, 0, 0, 0));
	else 
	{
		color = get_form_color(data->scene, hit_point, ray);
		free(hit_point);
		return(color);
	}
}
