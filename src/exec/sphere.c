/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:49 by eorer             #+#    #+#             */
/*   Updated: 2023/10/27 17:27:33 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

//float	is_hiting_sphere(t_ray ray, t_sphere *sphere);
//
//	// NE PAS OUBLIER DE FREE LE HIT !!!!!!!!!!!!!!!!!!!!!!!!//
//t_hit	*get_closest_sphere(t_data *data, t_ray ray)
//{
//	t_sphere	*tmp;
//	t_hit	*hit_point;
//	float	min;
//	float	t;
//
//	tmp = data->scene->sphere;
//	if (!tmp)
//		return (NULL);
//	hit_point = ft_calloc(sizeof(t_hit), 1);
//	if (!hit_point)
//		return (data->error = MALLOC_ERR, NULL);
//	min = 0;
//	while (tmp)
//	{
//		t = is_hiting_sphere(ray, tmp);
//		if (t != -1)
//		{
//			if (min == 0 || t < min)
//			{
//				min = t;
//				hit_point->obj = tmp;
//				hit_point->color = tmp->colors;
//				hit_point->point = intersection(ray, min);
//				hit_point->type = SPHERE;
//			}
//		}
//		tmp = tmp->next;
//	}
//	if (!min)
//		return (NULL);
//	return (hit_point);
//}
//
//float	is_hiting_sphere(t_ray ray, t_sphere *sphere)
//=======
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
