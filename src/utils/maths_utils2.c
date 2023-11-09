/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:26:35 by bastien           #+#    #+#             */
/*   Updated: 2023/11/08 16:31:31 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_colors	new_color(int red, int green, int blue)
{
	t_colors	result;

	result.red = red;
	result.green = green;
	result.blue = blue;
	return (result);
}

t_colors	add_colors(t_colors ca, t_colors cb)
{
	t_colors	result;

	result.red = ca.red + cb.red;
	result.green = ca.green + cb.green;
	result.blue = ca.blue + cb.blue;
	return (result);
}

t_vect	add_vectors(t_vect vect_a, t_vect vect_b)
{
	t_vect	result;

	result.x = vect_a.x + vect_b.x;
	result.y = vect_a.y + vect_b.y;
	result.z = vect_a.z + vect_b.z;
	return (result);
}

t_vect	sous_vectors(t_vect vect_a, t_vect vect_b)
{
	t_vect	result;

	result.x = vect_a.x - vect_b.x;
	result.y = vect_a.y - vect_b.y;
	result.z = vect_a.z - vect_b.z;
	return (result);
}

t_vect	mult_vect(t_vect vector, t_vect vector2)
{
	return ((t_vect){vector2.x * vector.x, vector2.y
		* vector.y, vector2.z * vector.z});
}
