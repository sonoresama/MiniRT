/* *************clang -Wall -Wextra -Werror -g    -c -o bonus/exec/light_shadow.o bonus/exec/light_shadow.c
clang -Wall -Wextra -Werror -g    -c -o ************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:34:33 by eorer             #+#    #+#             */
/*   Updated: 2023/11/30 14:22:27 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

#define LEFT 10
#define RIGHT 11
#define UP 12
#define DOWN 13
#define FRONT 14
#define BACK 15

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

t_system	init_system(t_camera *camera)
{
	t_vect up;
	t_vect	x;
	t_vect	y;
	t_vect	z;

	up = new_vector(0, 1, 0);
	z = ft_normalize(camera->look);
	if (camera->look.x == 0 && camera->look.z == 0 && camera->look.y > 0)
		up = new_vector(0, 0, 1);
	else if (camera->look.x == 0 && camera->look.z == 0 && camera->look.y < 0)
		up = new_vector(0, 0, -1);
	x = cross(up, z);
	y = cross(z, x);
	return ((t_system){x, y, z});
}

int	handle_keys(int keycode, t_data *data)
{
	t_system	system;
	t_win_list	*tmp;


	system = init_system(data->scene->camera);
	if (keycode == XK_Left)
		data->scene->camera->pos.xyz -= system.x.xyz;
	else if (keycode == XK_Right)
		data->scene->camera->pos.xyz += system.x.xyz;
	else if (keycode == XK_Up)
		data->scene->camera->pos.xyz += system.z.xyz;
	else if (keycode == XK_Down)
		data->scene->camera->pos.xyz -= system.z.xyz;
	else if (keycode == XK_o)
		data->scene->camera->pos.y += 1;
	else if (keycode == XK_l)
		data->scene->camera->pos.y -= 1;
	else if (keycode == XK_a)
	{
		mult_mat_vect_l(&data->scene->camera->look, system);
		ft_calc_matrix_cam(data->scene->camera);
	}
	else if (keycode == XK_d)
	{
		mult_mat_vect_r(&data->scene->camera->look, system);
		ft_calc_matrix_cam(data->scene->camera);
	}
	else if (keycode == XK_w)
	{
		mult_mat_vect_u(&data->scene->camera->look, system);
		ft_calc_matrix_cam(data->scene->camera);
	}
	else if (keycode == XK_s)
	{
		mult_mat_vect_d(&data->scene->camera->look, system);
		ft_calc_matrix_cam(data->scene->camera);
	}
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
	else if(handle_keys(keycode, data))
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		return (1);
	}
	return (0);
}
