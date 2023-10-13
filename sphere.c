/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:20:19 by eorer             #+#    #+#             */
/*   Updated: 2023/10/13 16:56:28 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//void	is_hiting_sphere(t_ray ray, t_sphere sphere, t_vect **hit_point)
//{
//	float	a;
//	float	b;
//	float	c;
//	float	d;
//	float	t;
//
//	a = mult_vectors(ray.direction, ray.direction);
//	b = mult_vectors(mult_const_vector(ray.direction, 2), sous_vectors(ray.origin, sphere.center));
//	c = mult_vectors(sous_vectors(ray.origin, sphere.center), sous_vectors(ray.origin, sphere.center)) - pow(sphere.radius, 2);
//	d = pow(b, 2) - 4 * a * c ;
//	if (d < 0)
//	{
//		*hit_point = NULL;
//		return ;
//	}
//	else if (d == 0)
//		t = (-b + sqrt(d)) / (2 * a);
//	else
//		t = fmin((-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a));
//	**hit_point = add_vectors(ray.origin, mult_const_vector(ray.direction, t));
//}

float	is_hiting_sphere(t_ray ray, t_sphere)
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
		return ((-b + sqrt(d)) / (2 * a));
	else
		return (fmin((-b + sqrt(d)) / (2 * a), (-b - sqrt(d)) / (2 * a)));
}

t_vect	v_normal_sphere(t_sphere sphere, t_vect hit_point)
{
	t_vect	result;

	result = sous_vectors(hit_point, sphere.center);
	ft_normalize(&result);
	return (result);
}
