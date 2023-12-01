/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_tito.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:54:16 by eorer             #+#    #+#             */
/*   Updated: 2023/12/01 13:50:07 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	init_matrix(float matrix[3][3], t_vect u, float angle)
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

static void	ft_calc_matrix_cam(t_camera *camera)
{
	t_vect	forward;
	t_vect	right;
	t_vect	up;
	t_vect	tmp;

	tmp = new_vector(0, 1, 0);
	if (camera->look.x == 0 && camera->look.z == 0 && camera->look.y > 0)
		tmp = new_vector(0, 0, 1);
	else if (camera->look.x == 0 && camera->look.z == 0 && camera->look.y < 0)
		tmp = new_vector(0, 0, -1);
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

int	ft_rotate(t_system system, t_data *data, int keycode)
{
	float	matrix[3][3];

	ft_bzero(matrix, sizeof(float) * 3 * 3);
	if (keycode == XK_d)
		init_matrix(matrix, system.y, -10);
	else if (keycode == XK_a)
		init_matrix(matrix, system.y, 10);
	else
		return (0);
	data->scene->camera->look = mat_rotate(matrix, data->scene->camera->look);
	ft_calc_matrix_cam(data->scene->camera);
	return (1);
}

int	handle_keys(int keycode, t_data *data)
{
	t_system	system;
	t_win_list	*tmp;

	system = init_system(data->scene->camera);
	if (ft_translate(system, data, keycode) == 0
		&& ft_rotate(system, data, keycode) == 0)
		return (0);
	if (init_thread(data))
	{
		tmp = data->win;
		return (ft_clear_all(data->scene),
			mlx_destroy_display(data->mlx), free(data->mlx),
			free(tmp->gc), free(data->win), 1);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->mlx_img.img, 0, 0);
	return (0);
}

int	keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		return (1);
	}
	else if (handle_keys(keycode, data))
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		return (1);
	}
	return (0);
}
