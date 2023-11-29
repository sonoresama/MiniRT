/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:28:07 by bastien           #+#    #+#             */
/*   Updated: 2023/11/29 12:44:50 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vect	mult(t_vect vector, double c)
{
	return ((t_vect){c * vector.x, c * vector.y, c * vector.z});
}

double	dot(t_vect a, t_vect b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vect	cross(t_vect a, t_vect b)
{
	return (a.yzx * b.zxy - a.zxy * b.yzx);
}

//t_vect	cross(t_vect a, t_vect b)
//{
//	t_vect	result;
//
//	result.x = a.y * b.z - a.z * b.y;
//	result.y = a.z * b.x - a.x * b.z;
//	result.z = a.x * b.y - a.y * b.x;
//	return (result);
//}

t_vect	mult_mat_vect(float mat[4][4], t_vect vector)
{
	t_vect	result;

	result.x = mat[0][0] * vector.x + mat[0][1]
		* vector.y + mat[0][2] * vector.z;
	result.y = mat[1][0] * vector.x + mat[1][1]
		* vector.y + mat[1][2] * vector.z;
	result.z = mat[2][0] * vector.x + mat[2][1]
		* vector.y + mat[2][2] * vector.z;
	return (result);
}

double	rad(double angle)
{
	return (angle * M_PI / 180);
}
