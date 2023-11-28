/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_plan.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:28:18 by blerouss          #+#    #+#             */
/*   Updated: 2023/11/23 15:19:52 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	get_closest_plan(t_ray ray, t_plan *plan, t_hit *first_hit_point)
{
	float	t;

	if (!plan)
		return ;
	while (plan)
	{
		t = is_hiting_plan(ray, plan);
		if (t >= 0)
		{
			if (!first_hit_point->time
				|| (t > 0.01 && t < first_hit_point->time))
			{
				first_hit_point->time = t;
				first_hit_point->point = intersection(ray, t);
				first_hit_point->normal = plan->vecteur;
				if (dot(plan->vecteur, ray.direction) > 0)
					first_hit_point->normal = mult(plan->vecteur, -1);
				first_hit_point->type = PLAN;
				first_hit_point->obj = plan;
				first_hit_point->color = plan->colors;
			}
		}
		plan = plan->next;
	}
}
