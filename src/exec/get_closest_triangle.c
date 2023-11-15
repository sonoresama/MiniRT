/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_closest_triangle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:33:11 by eorer             #+#    #+#             */
/*   Updated: 2023/11/15 13:00:36 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	inside_test(t_vect point, t_tr *tr, t_vect normal)
{
	t_vect	edge_a;
	t_vect	edge_b;
	t_vect	edge_c;
	t_vect	c;

	edge_a = sous_vectors(tr->b, tr->a);
	edge_b = sous_vectors(tr->c, tr->b);
	edge_c = sous_vectors(tr->a, tr->c);
	c = sous_vectors(point, tr->a);
	if (dot(normal, cross(edge_a, c)) < 0)
		return(0);
	c = sous_vectors(point, tr->b);
	if (dot(normal, cross(edge_b, c)) < 0)
		return(0);
	c = sous_vectors(point, tr->c);
	if (dot(normal, cross(edge_c, c)) < 0)
		return(0);
	return (1);
}            

void	set_hit_tr(t_tr *tr, float t, t_hit *hit_point, t_vect normal, t_vect point)
{
	hit_point->time = t;
	hit_point->point = point;
	hit_point->normal = normal;
	hit->type = TRIANGLE;
	hit->obj = tr;
	hit->color = tr->colors;
}

int	is_hiting_triangle(t_ray ray, t_tr *tr, t_hit *hit_point)
{
	t_vect	normal;
	t_vect	u;
	t_vect	v;
	t_vect	point;
	t_plan	plan;
	float	t;
	int	i;

	u = sous_vectors(tr->b, tr->a);
	v = sous_vectors(tr->c, tr->a);
	normal = ft_normalize(cross(u, v));
	plan.start = tr->a;
	plan.vecteur = normal;
	plan.color = tr->color;
	t = is_hiting_plan(ray, &plan);
	if (t == -1)
		return (0);
	point = intersection(ray, t);
	if (!inside_test(point, tr))
		return (0);
//	if (dot(normal, ray.direction) > 0)
//		normal = mult(normal, -1);
	set_hit_tr(tr, t, hit_point);
	return (1);
}

void	get_closest_triangle(t_ray ray, t_tr *tr, t_hit *hit_point)
{
	float	t;
	t_hit	*tmp;

	tmp = ft_calloc(sizeof(t_hit), 1);
	if (!tmp || !tr)
		return ;
	while (tr)
	{
		t = is_hiting_triangle(ray, tr, tmp);
		if (tmp->time > 0.001 && tmp->time < hit_point->time)
			hit_point = tmp;
		tr = tr->next;
	}
	free(tmp);
}
