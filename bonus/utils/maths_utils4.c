/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:56:32 by blerouss          #+#    #+#             */
/*   Updated: 2023/12/01 13:48:22 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vect	mult_mat_vect_l(t_vect *vector, t_system system)
{
	t_vect	tmp;

	(void)system;
	tmp.x = vector->x;
	tmp.y = vector->y;
	tmp.z = vector->z;
	vector->x = cos(0.2618) * tmp.x + sin(0.2618) * tmp.z;
	vector->y = tmp.y;
	vector->z = -sin(0.2618) * tmp.x + cos(0.2618) * tmp.z;
	return (*vector);
}

t_vect	mult_mat_vect_r(t_vect *vector, t_system system)
{
	t_vect	tmp;

	(void)system;
	tmp.x = vector->x;
	tmp.y = vector->y;
	tmp.z = vector->z;
	vector->x = cos(0.2618) * tmp.x + -sin(0.2618) * tmp.z;
	vector->y = tmp.y;
	vector->z = sin(0.2618) * tmp.x + cos(0.2618) * tmp.z;
	return (*vector);
}

t_vect	mult_mat_vect_u(t_vect *vector, t_system system)
{
	t_vect	tmp;

	tmp.x = vector->x;
	tmp.y = vector->y;
	tmp.z = vector->z;
	vector->x = system.x.x;
	vector->y = system.x.y * system.x.y * (1 - cos(0.2618)) + cos(0.2618)
		+ system.x.y * system.x.z * (1 - cos(0.2618)) - system.x.x
		* sin(0.2618);
	vector->z = system.x.y * system.x.z * (1 - cos(0.2618)) + system.x.x
		* sin(0.2618) + system.x.z * system.x.z * (1 - cos(0.2618))
		+ cos(0.2618);
	if (vector->y == -1)
	{
		vector->x = tmp.x;
		vector->y = tmp.y;
		vector->z = tmp.z;
		return (*vector);
	}
	return (*vector);
}

t_vect	mult_mat_vect_d(t_vect *vector, t_system system)
{
	t_vect	tmp;

	tmp.x = vector->x;
	tmp.y = vector->y;
	tmp.z = vector->z;
	vector->x = system.x.x * system.x.x * (1 - cos(0.2618)) + cos(0.2618)
		+ system.x.x * system.x.y * (1 - cos(0.2618)) - system.x.x
		* sin(0.2618);
	vector->y = system.x.x * system.x.y * (1 - cos(0.2618)) + system.x.x
		* sin(0.2618) + system.x.y * system.x.y * (1 - cos(0.2618))
		+ cos(0.2618);
	vector->z = system.x.z;
	if (vector->y == 1)
	{
		vector->x = tmp.x;
		vector->y = tmp.y;
		vector->z = tmp.z;
		return (*vector);
	}
	return (*vector);
}

t_vect	mat_rotate(float matrix[3][3], t_vect u)
{
	t_vect	result;

	result.x = matrix[0][0] * u.x + matrix[0][1] * u.y + matrix[0][2] * u.z;
	result.y = matrix[1][0] * u.x + matrix[1][1] * u.y + matrix[1][2] * u.z;
	result.z = matrix[2][0] * u.x + matrix[2][1] * u.y + matrix[2][2] * u.z;
	return (result);
}
