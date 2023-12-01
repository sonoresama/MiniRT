/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_tito.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:54:16 by eorer             #+#    #+#             */
/*   Updated: 2023/12/01 14:29:03 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	ft_translate(t_system system, t_data *data, int keycode)
{
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
	else
		return(0);
	return (1);
}

int	ft_rotate(t_system system, t_data *data, int keycode)
{
	float matrix[3][3];

	ft_bzero(matrix, sizeof(float) * 3 * 3);
	if (keycode == XK_a)
		init_rot_matrix(matrix, system.y, 10);
	else if (keycode == XK_d)
		init_rot_matrix(matrix, system.y, -10);
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
	else if(handle_keys(keycode, data))
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		return (1);
	}
	return (0);
}
