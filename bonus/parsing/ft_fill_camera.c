/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:46:03 by blerouss          #+#    #+#             */
/*   Updated: 2023/12/01 14:35:42 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	init_matrix(float matrix[4][4])
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[0][3] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[1][3] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
	matrix[2][3] = 0;
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
}

static void	ft_calc_matrix_cam(t_camera *camera)
{
	t_vect	forward;
	t_vect	right;
	t_vect	up;
	t_vect	tmp;

	init_matrix(camera->matrix);
	tmp = new_vector(0, 1, 0);
	if (camera->look.x == 0 && camera->look.z == 0 && camera->look.y > 0)
		tmp = new_vector(0, 0, 1);
	else if (camera->look.x == 0 && camera->look.z == 0 && camera->look.y < 0)
		tmp = new_vector(0, 0, -1);
	camera->look.x = -camera->look.x;
	camera->look.y = -camera->look.y;
	forward = ft_normalize(camera->look);
	right = cross(tmp, forward);
	up = cross(forward, right);
	camera->matrix[0][0] = right.x;
	camera->matrix[0][1] = right.y;
	camera->matrix[0][2] = right.z;
	camera->matrix[1][0] = up.x;
	camera->matrix[1][1] = up.y;
	camera->matrix[1][2] = up.z;
	camera->matrix[2][0] = forward.x;
	camera->matrix[2][1] = forward.y;
	camera->matrix[2][2] = forward.z;
}

int	ft_fill_camera(char **tab, t_scene *scene, int line)
{
	if (scene->camera)
		return (printf("%s", DTC_ERR), 1);
	scene->camera = ft_calloc(sizeof(t_camera), 1);
	if (!scene->camera)
		return (printf("%s", MAL_ERR), 1);
	if (ft_fill_vector(tab[1], &scene->camera->pos, line))
		return (printf("%s%i\n", POS_ERR, line), 1);
	if (ft_fill_vector(tab[2], &scene->camera->look, line)
		|| scene->camera->look.x < -1 || scene->camera->look.x > 1
		|| scene->camera->look.y < -1 || scene->camera->look.y > 1
		|| scene->camera->look.z < -1 || scene->camera->look.z > 1)
		return (printf("%s%i\n", VEC_ERR, line), 1);
	if (ft_atod(tab[3], &scene->camera->fov) || scene->camera->fov < 0
		|| scene->camera->fov > 180)
		return (printf("%s%i\n", FOV_ERR, line), 1);
	scene->camera->scale = tan(rad(scene->camera->fov) * 0.5);
	ft_calc_matrix_cam(scene->camera);
	return (0);
}
