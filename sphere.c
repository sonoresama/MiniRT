/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:20:19 by eorer             #+#    #+#             */
/*   Updated: 2023/10/16 13:17:38 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

float	is_hiting_sphere(t_ray ray, t_sphere sphere)
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	t;

	a = mult_vectors(ray.direction, ray.direction);
	b = mult_vectors(mult_const_vector(ray.direction, 2), sous_vectors(ray.origin, sphere.center));
	c = mult_vectors(sous_vectors(ray.origin, sphere.center), sous_vectors(ray.origin, sphere.center)) - pow(sphere.radius, 2);
	d = pow(b, 2) - 4 * a * c ;
	if (d < 0)
		return (-1);
	else if (d == 0)
		t = (-b + sqrt(d)) / (2 * a);
	else
		t = fmin((-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a));
	return (t);
}

t_vect	v_normal_sphere(t_sphere sphere, t_vect hit_point)
{
	t_vect	result;

	result = sous_vectors(hit_point, sphere.center);
	ft_normalize(&result);
	return (result);
}

//float	get_closest_sphere(t_ray ray, t_data *data)
//{
//	t_sphere	*tmp;
//	float	t;
//	float	min_dist;
//
//	tmp = data->sphere;
//	min_dist = 0;
//	while (tmp->sphere)
//	{
//		t = is_hiting_sphere(ray, *tmp);
//		if (!min_dist || t < min_dist)
//			min_dist = t;
//		tmp->next;
//	}
//	return (min_dist);
//}
