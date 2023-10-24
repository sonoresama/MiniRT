/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_plan.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:28:18 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/24 15:36:06 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	get_closest_plan(t_ray ray, t_plan *plan, t_hit *first_hit_point)
{
	float	p_dot;
	float	t;

	while (plan)
	{
		p_dot = dot(ray.direction, ft_normalize(plan->vecteur));
		if (p_dot >= 0)
		{
			t = dot(sous_vectors(plan->start, ray.origin),
				ft_normalize(plan->vecteur)) / p_dot;
			if (t > 0 && t < first_hit_point->time)
			{
				first_hit_point->time = t;
				first_hit_point->point = intersection(ray, t);
				first_hit_point->normal = v_normal_plan((*plan));
				first_hit_point->type = PLAN;
				first_hit_point->obj = plan;
			}
		}
		plan = plan->next;
	}
}
