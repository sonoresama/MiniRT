/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:32:23 by eorer             #+#    #+#             */
/*   Updated: 2023/10/26 18:44:22 by bastien          ###   ########.fr       */
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

t_vect	mult(t_vect vector, double c)
{
	return ((t_vect){c * vector.x, c * vector.y, c * vector.z});
}

double	dot(t_vect a, t_vect b)
{
	double	result;

	result = a.x * b.x + a.y * b.y + a.z * b.z; 
	return (result);
}

t_vect	cross_product(t_vect a, t_vect b)
{
	t_vect	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vect	mult_mat_vect(float mat[4][4], t_vect vector)
{
	t_vect	result;

	result.x = mat[0][0] * vector.x + mat[0][1] * vector.y + mat[0][2] * vector.z;
	result.y = mat[1][0] * vector.x + mat[1][1] * vector.y + mat[1][2] * vector.z;
	result.z = mat[2][0] * vector.x + mat[2][1] * vector.y + mat[2][2] * vector.z;
	return (result);
}

double	rad(double angle)
{
	return (angle * M_PI / 180);
}

// In this function, if vector.w = 0 then we rotate a vectorm if vector.w = 1, we transform and translate a point

//t_vect_4 transpose_cam(t_4x4mat mat, t_vect4 origin, t_vect4 destination)
//{
//	t_vect	result;
//
//	result.x = mat[0][0] * vector.x + mat[0][1] * vector.y + mat[0][2] * vector.z; 
//	result.y = mat[1][0] * vector.x + mat[1][1] * vector.y + mat[1][2] * vector.z; 
//	result.z = mat[2][0] * vector.x + mat[2][1] * vector.y + mat[2][2] * vector.z; 
//	return (result);
//}

t_vect	ft_normalize(t_vect vector)
{
	float	norm;
	t_vect	vect;

	norm = ft_norm(vector);
	if (!norm)
		return (new_vector(0, 0, 0));
	vect.x = vector.x / norm;
	vect.y = vector.y / norm;
	vect.z = vector.z / norm;
	return (vect);
}

float	ft_norm(t_vect vect)
{
	float	norm;

	norm = sqrt(pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2));
	return (norm);
}

t_vect	intersection(t_ray ray, float t)
{
	t_vect	point;

	point = add_vectors(ray.origin, mult(ray.direction, t));
	return (point);
}
