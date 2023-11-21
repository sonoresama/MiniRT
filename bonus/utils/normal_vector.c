/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:34:29 by eorer             #+#    #+#             */
/*   Updated: 2023/10/24 16:23:14 by blerouss         ###   ########.fr       */
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
