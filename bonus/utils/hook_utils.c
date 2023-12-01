/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:42:32 by eorer             #+#    #+#             */
/*   Updated: 2023/12/01 14:51:39 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_system	init_system(t_camera *camera)
{
	t_vect	up;
	t_vect	x;
	t_vect	y;
	t_vect	z;

	up = new_vector(0, 1, 0);
	z = ft_normalize(camera->look);
	if (camera->look.x == 0 && camera->look.z == 0 && camera->look.y > 0)
		up = new_vector(0, 0, 1);
	else if (camera->look.x == 0 && camera->look.z == 0 && camera->look.y < 0)
		up = new_vector(0, 0, -1);
	x = ft_normalize(cross(up, z));
	y = ft_normalize(cross(z, x));
	return ((t_system){x, y, z});
}

void	init_rot_matrix(float matrix[3][3], t_vect u, float angle)
{
	float	c;
	float	s;

	u = ft_normalize(u);
	c = cos(rad(angle));
	s = sin(rad(angle));
	matrix[0][0] = u.x * u.x * (1 - c) + c;
	matrix[0][1] = u.x * u.y * (1 - c) - u.z * s;
	matrix[0][2] = u.x * u.z * (1 - c) + u.y * s;
	matrix[1][0] = u.y * u.x * (1 - c) + u.z * s;
	matrix[1][1] = u.y * u.y * (1 - c) + c;
	matrix[1][2] = u.y * u.z * (1 - c) - u.x * s;
	matrix[2][0] = u.z * u.x * (1 - c) - u.y * s;
	matrix[2][1] = u.z * u.y * (1 - c) + u.x * s;
	matrix[2][2] = u.z * u.z * (1 - c) + c;
}

t_vect	mat_rotate(float matrix[3][3], t_vect u)
{
	t_vect	result;

	result.x = matrix[0][0] * u.x + matrix[0][1] * u.y + matrix[0][2] * u.z;
	result.y = matrix[1][0] * u.x + matrix[1][1] * u.y + matrix[1][2] * u.z;
	result.z = matrix[2][0] * u.x + matrix[2][1] * u.y + matrix[2][2] * u.z;
	return (ft_normalize(result));
}
