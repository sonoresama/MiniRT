/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:49 by eorer             #+#    #+#             */
/*   Updated: 2023/11/08 17:34:32 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	get_closest_sphere(t_ray ray, t_sphere *sphere, t_hit *first_hit_point)
{
	float	t;

	if (!sphere)
		return ;
	while (sphere)
	{
		t = is_hiting_sphere(ray, sphere);
		if (t != -1)
		{
			if (t > 0.001 && (first_hit_point->time == 0
					|| t < first_hit_point->time))
			{
				first_hit_point->time = t;
				first_hit_point->obj = sphere;
				first_hit_point->point = intersection(ray,
						first_hit_point->time);
				first_hit_point->type = SPHERE;
				first_hit_point->normal = v_normal_sphere(*sphere,
						first_hit_point->point);
				first_hit_point->color = sphere->colors;
			}
		}
		sphere = sphere->next;
	}
	return ;
}
