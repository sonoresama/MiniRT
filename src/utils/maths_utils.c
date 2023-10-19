/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:32:23 by eorer             #+#    #+#             */
/*   Updated: 2023/10/19 16:39:45 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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

t_vect	mult_const_vector(t_vect vector, double c)
{
	return ((t_vect){c * vector.x, c * vector.y, c * vector.z});
}

double	dot(t_vect vect_a, t_vect vect_b)
{
	double	result;

	result = vect_a.x * vect_b.x + vect_a.y * vect_b.y + vect_a.z * vect_b.z; 
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

t_vect	mult_mat_vect(double mat[3][3], t_vect vector)
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

// angle must be in radian

t_vect	rotate_cam(double angle, char axis, t_vect vector)
{
	if (axis == 1)
	{
		return (mult_mat_vect((double[3][3]){{1, 0, 0}, {0, cos(angle), -sin(angle)}, {0, sin(angle), cos(angle)}}, vector));
	}
	else if (axis == 2)
	{
		return (mult_mat_vect((double[3][3]){{cos(angle), 0, sin(angle)}, {0, 1, 0}, {-sin(angle), 0, cos(angle)}}, vector));
	}
	else 
	{
		return (mult_mat_vect((double[3][3]){{cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}}, vector));
	}
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

void	ft_normalize(t_vect *vector)
{
	float	norm;

	norm = sqrt(pow(vector->x, 2) + pow(vector->x, 2) + pow(vector->x, 2));
	if (!norm)
		return ;
	vector->x = vector->x / norm;
	vector->y = vector->y / norm;
	vector->z = vector->z / norm;
}
