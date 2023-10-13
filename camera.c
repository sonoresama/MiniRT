/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:33:43 by eorer             #+#    #+#             */
/*   Updated: 2023/10/13 14:30:53 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	generate_rot_matrix(t_data *data)
{
	t_vect	forward;
	t_vect	right;
	t_vect	up;
	t_vect	tmp;

	tmp = new_vector(0, 1, 0);
	forward = data->camera.look;
	right = cross_product(tmp, forward);
	ft_normalize(&right);
	up = cross_product(forward, right);
	data->camera.matrix[0][0] = right.x;
	data->camera.matrix[0][1] = right.y;
	data->camera.matrix[0][2] = right.z;
	data->camera.matrix[1][0] = up.x;
	data->camera.matrix[1][1] = up.y;
	data->camera.matrix[1][2] = up.z;
	data->camera.matrix[2][0] = forward.x;
	data->camera.matrix[2][1] = forward.y;
	data->camera.matrix[2][2] = forward.z;
}

t_vect	camera_to_world(double matrix[3][3], t_vect *vector, t_vect dest)
{
	t_vect	result;

	result = add_vectors(*vector, dest);
	result.x = vector->x * matrix[0][0] + vector->y * matrix[1][0] + vector->z * matrix[2][0];
	result.y = vector->x * matrix[0][1] + vector->y * matrix[1][1] + vector->z * matrix[2][1];
	result.z = vector->x * matrix[0][2] + vector->y * matrix[1][2] + vector->z * matrix[2][2];
	return (result);
}
