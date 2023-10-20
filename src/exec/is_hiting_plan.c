/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hiting_plan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:45:08 by bastien           #+#    #+#             */
/*   Updated: 2023/10/20 17:46:44 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	is_hiting_plan(t_ray ray, t_plan *plan, t_hit *first_hit_point)
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
				first_hit_point->type = PLAN;
				first_hit_point->obj = plan;
			}
		}
		plan = plan->next;
	}
}
