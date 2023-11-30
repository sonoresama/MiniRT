/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_triangle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:33:11 by eorer             #+#    #+#             */
/*   Updated: 2023/11/30 14:41:05 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	inside_test(t_vect point, t_triangle *triangle, t_vect normal)
{
	t_vect	edge_a;
	t_vect	edge_b;
	t_vect	edge_c;
	t_vect	c;

	edge_a = triangle->b.xyz - triangle->a.xyz;
	edge_b = triangle->c.xyz - triangle->b.xyz;
	edge_c = triangle->a.xyz - triangle->c.xyz;
	c = point.xyz - triangle->a.xyz;
	if (dot(normal, cross(edge_a, c)) < 0)
		return (0);
	c = point.xyz - triangle->b.xyz;
	if (dot(normal, cross(edge_b, c)) < 0)
		return (0);
	c = point.xyz - triangle->c.xyz;
	if (dot(normal, cross(edge_c, c)) < 0)
		return (0);
	return (1);
}

void	set_hit_triangle(float t, t_hit *hit_point, t_vect normal, t_vect point)
{
	if (!hit_point)
		return ;
	hit_point->time = t;
	hit_point->point = point;
	hit_point->normal = normal;
	hit_point->type = TRIANGLE;
}

void	cpy_hit(t_hit *dst, t_hit *adr)
{
	dst->time = adr->time;
	dst->point = adr->point;
	dst->normal = adr->normal;
	dst->type = adr->type;
	dst->obj = adr->obj;
	dst->color = adr->color;
}

void	get_closest_triangle(t_ray ray, t_triangle *triangle, t_hit *hit_point)
{
	t_hit	tmp;

	if (!triangle || !hit_point)
		return ;
	while (triangle)
	{
		ft_bzero(&tmp, sizeof(t_hit));
		if (is_hiting_triangle(ray, triangle, &tmp)
			&& tmp.time > 0.001
			&& (hit_point->time == 0 || tmp.time < hit_point->time))
			cpy_hit(hit_point, &tmp);
		triangle = triangle->next;
	}
}
