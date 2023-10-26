/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:46:03 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/26 18:47:22 by bastien          ###   ########.fr       */
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

static void	fill_matrix_rotation(float matrix[4][4], double angle, t_vect rot)
{
	matrix[0][0] = cos(angle) + rot.x * rot.z * (1 - cos(angle));
	matrix[0][1] = rot.x * rot.y * (1 - cos(angle)) - rot.z * sin(angle);
	matrix[0][2] = rot.x * rot.z * (1 - cos(angle)) + rot.y * sin(angle);
	matrix[1][0] = rot.y * rot.x * (1 - cos(angle)) + rot.z * sin(angle);
	matrix[1][1] = cos(angle) + rot.y * rot.y * (1 - cos(angle));
	matrix[1][2] = rot.y * rot.z * (1 - cos(angle)) - rot.x * sin(angle);
	matrix[2][0] = rot.z * rot.x * (1 - cos(angle)) - rot.y * sin(angle);
	matrix[2][1] = rot.z * rot.y * (1 - cos(angle)) + rot.x * sin(angle);
	matrix[2][2] = cos(angle) + rot.z * rot.z * (1 - cos(angle));

}

static void	ft_calc_matrix_cam(t_camera *camera)
{
	double	angle;
	t_vect	rotation_axe;

	init_matrix(camera->matrix); 
	angle = acos(dot(camera->look, new_vector(0, 0, -1)) / (ft_norm(camera->look) * ft_norm(new_vector(0, 0, -1))));
	rotation_axe = ft_normalize(cross_product(camera->look, new_vector(0, 0, -1)));
	fill_matrix_rotation(camera->matrix, angle, rotation_axe);
//	print_vect(rotation_axe);
//	printf("angle = %f\n", angle);
//	printf("| %f %f %f |\n", camera->matrix[0][0], camera->matrix[0][1], camera->matrix[0][2]);
//	printf("| %f %f %f |\n", camera->matrix[1][0], camera->matrix[1][1], camera->matrix[1][2]);
//	printf("| %f %f %f |\n", camera->matrix[2][0], camera->matrix[2][1], camera->matrix[2][2]);
}

int	ft_fill_camera(char **tab, t_scene *scene, int line)
{
	if (scene->camera)
		return (printf("%s", DTC_ERR), 1);
	scene->camera = ft_calloc(sizeof(t_camera), 1);
	if (!scene->camera)
		return (printf("%s", MAL_ERR), 1);
	if (ft_fill_vector(tab[1], &scene->camera->pos, line))
		return (1);
	if (ft_fill_vector(tab[2], &scene->camera->look, line))
		return (1);
	if (ft_atod(tab[3], &scene->camera->fov) || scene->camera->fov < 0
		|| scene->camera->fov > 180)
		return (printf("%s%i\n", FOV_ERR, line), 1);
	ft_calc_matrix_cam(scene->camera);
//	print_vect(scene->camera->pos);
//	print_vect(scene->camera->look);
	return (0);
}
