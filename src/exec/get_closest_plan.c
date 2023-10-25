/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_plan.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:28:18 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/25 16:10:01 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#define ABS(x) x < 0 ? -1 * x : x

void	get_closest_plan(t_ray ray, t_plan *plan, t_hit *first_hit_point)
{
	float	p_dot;
	float	t;
	
	while (plan)
	{
		p_dot = dot(ray.direction, ft_normalize(plan->vecteur));
		if (p_dot > 0)
		{
			t = dot(sous_vectors(plan->start, ray.origin),
				ft_normalize(plan->vecteur)) / p_dot;
			t = ABS(t);
			if (!first_hit_point->time || (t > 0.0 && t < first_hit_point->time))
			{
				first_hit_point->time = t;
				first_hit_point->point = intersection(ray, t);
				first_hit_point->normal = plan->vecteur;
				first_hit_point->type = PLAN;
				first_hit_point->obj = plan;
				first_hit_point->color = plan->colors;
			}
		}
		plan = plan->next;
	}
}
