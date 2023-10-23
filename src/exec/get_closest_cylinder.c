/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:27:09 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/23 17:29:11 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	get_closest_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *first_hit_point)
{
	float	p_dot;
	float	t;

	while (cylinder)
	{
		p_dot = dot(ray.direction, ft_normalize(cylinder->vecteur));
		if (p_dot >= 0)
		{
			t = dot(sous_vectors(cylinder->start, ray.origin),
				ft_normalize(cylinder->vecteur)) / p_dot;
			if (t > 0 && t < first_hit_point->time)
			{
				first_hit_point->time = t;
				first_hit_point->point = intersection(ray, t);
				first_hit_point->type = CYLINDER;
				first_hit_point->obj = cylinder;
			}
		}
		cylinder = cylinder->next;
	}
}
