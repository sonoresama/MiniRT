/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:34:29 by eorer             #+#    #+#             */
/*   Updated: 2023/10/24 15:35:54 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vect	v_normal_sphere(t_sphere sphere, t_vect hit_point)
{
	t_vect	result;

	result = sous_vectors(hit_point, sphere.center);
	result = ft_normalize(result);
	return (result);
}

t_vect	v_normal_plan(t_plan plan)
{
	t_vect	result;
	t_vect	p2;

	p2 = add_vectors(plan.start, plan.vecteur);
	p2 = sous_vectors(p2, plan.start);
	result.x = p2.y * plan.vecteur.z - p2.z * plan.vecteur.y;
	result.y = p2.z * plan.vecteur.x - p2.x * plan.vecteur.z;
	result.z = p2.x * plan.vecteur.y - p2.y * plan.vecteur.x;
	return (result);
}

