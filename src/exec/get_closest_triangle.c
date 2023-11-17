/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_triangle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:33:11 by eorer             #+#    #+#             */
/*   Updated: 2023/11/17 18:06:46 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	inside_test(t_vect point, t_triangle *triangle, t_vect normal)
{
	t_vect	edge_a;
	t_vect	edge_b;
	t_vect	edge_c;
	t_vect	c;

	edge_a = sous_vectors(triangle->b, triangle->a);
	edge_b = sous_vectors(triangle->c, triangle->b);
	edge_c = sous_vectors(triangle->a, triangle->c);
	c = sous_vectors(point, triangle->a);
	if (dot(normal, cross(edge_a, c)) < 0)
		return(0);
	c = sous_vectors(point, triangle->b);
	if (dot(normal, cross(edge_b, c)) < 0)
		return(0);
	c = sous_vectors(point, triangle->c);
	if (dot(normal, cross(edge_c, c)) < 0)
		return(0);
	return (1);
}            

void	set_hit_triangle(t_triangle *triangle, float t, t_hit *hit_point, t_vect normal, t_vect point)
{
	hit_point->time = t;
	hit_point->point = point;
	hit_point->normal = normal;
	hit_point->type = TRIANGLE;
	hit_point->obj = triangle;
	hit_point->color = triangle->colors;
}

void	print_tr(t_triangle tr)
{
	printf("A : ");
	print_vect(tr.a);
	printf("B : ");
	print_vect(tr.b);
	printf("C : ");
	print_vect(tr.c);
}

int	is_hiting_triangle(t_ray ray, t_triangle *triangle, t_hit *hit_point)
{
	t_vect	normal;
	t_vect	u;
	t_vect	v;
	t_vect	point;
	t_plan	plan;
	float	t;

	u = sous_vectors(triangle->b, triangle->a);
	v = sous_vectors(triangle->c, triangle->a);
	normal = ft_normalize(cross(u, v));
	plan.vecteur = normal;
	plan.start = triangle->a;
	plan.colors = triangle->colors;
	t = is_hiting_plan(ray, &plan);
	if (t == -1)
		return (0);
	point = intersection(ray, t);
	if (!inside_test(point, triangle, plan.vecteur))
		return (0);
//	if (dot(normal, ray.direction) > 0)
//		normal = mult(normal, -1);
	if (t > 0.001 && t < hit_point->time)
		set_hit_triangle(triangle, t, hit_point, plan.vecteur, point);
	return (1);
}

void	get_closest_triangle(t_ray ray, t_triangle *triangle, t_hit *hit_point)
{
	float	t;
	t_hit	tmp;

	if (!triangle)
		return ;
	while (triangle)
	{
		ft_bzero(&tmp, sizeof(t_triangle));
		t = is_hiting_triangle(ray, triangle, &tmp);
		if (tmp.time > 0.001 && (hit_point->time == 0 || tmp.time < hit_point->time))
			*hit_point = tmp;
		triangle = triangle->next;
	}
}
