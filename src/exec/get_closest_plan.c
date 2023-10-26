/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_plan.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:28:18 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/26 17:34:43 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#define ABS(x) x < 0 ? -1 * x : x

void	get_closest_plan(t_ray ray, t_plan *plan, t_hit *first_hit_point)
{
	float	t;
	
	while (plan)
	{
		t = is_hiting_plan(ray, plan);
		if (t != -1.0)
		{
			t = ABS(t);
			if (!first_hit_point->time || (t > 0.0 && t < first_hit_point->time))
			{
				first_hit_point->time = t;
				first_hit_point->point = intersection(ray, t);
				if (dot(mult(ray.direction, -1), plan->vecteur) < 0)
					first_hit_point->normal = mult(plan->vecteur, -1);
				else
					first_hit_point->normal = plan->vecteur;
				first_hit_point->type = PLAN;
				first_hit_point->obj = plan;
				first_hit_point->color = plan->colors;
			}
		}
		plan = plan->next;
	}
}
