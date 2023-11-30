/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:34:33 by eorer             #+#    #+#             */
/*   Updated: 2023/11/30 16:42:55 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

#define LEFT 10
#define RIGHT 11
#define UP 12
#define DOWN 13
#define FRONT 14
#define BACK 15

typedef struct s_system{
	t_vect	x;
	t_vect	y;
	t_vect	z;
}	t_system;

t_system	init_system(t_camera *camera)
{
	t_vect up;
	t_vect	x;
	t_vect	y;
	t_vect	z;

	up = new_vector(0, 1, 0);
	z = ft_normalize(camera->look);
	x = cross(up, z);
	y = cross(z, x);
	return ((t_system){x, y, z});
}

void	ft_translate(t_data *data, int type, t_system system)
{
	if (type == UP)
		data->scene->camera->pos.y += 1;
	else if (type == DOWN)
		data->scene->camera->pos.y -= 1;
	else if (type == LEFT)
		data->scene->camera->pos.xyz -= system.x.xyz;
	else if (type == RIGHT)
		data->scene->camera->pos.xyz += system.x.xyz;
	else if (type == FRONT)
		data->scene->camera->pos.xyz += system.z.xyz;
	else if (type == BACK)
		data->scene->camera->pos.xyz -= system.z.xyz;
}

int	handle_keys(int keycode, t_data *data)
{
	t_system	system;
	t_win_list	*tmp;


	system = init_system(data->scene->camera);
	if (keycode == XK_Left)
		ft_translate(data, LEFT, system);
	else if (keycode == XK_Right)
		ft_translate(data, RIGHT, system);
	else if (keycode == XK_Up)
		ft_translate(data, FRONT, system);
	else if (keycode == XK_Down)
		ft_translate(data, BACK, system);
	else if (keycode == XK_o)
		ft_translate(data, UP, system);
	else if (keycode == XK_l)
		ft_translate(data, DOWN, system);

//	else if (keycode == XK_A)
//		ft_rotate(data, LEFT);
//	else if (keycode == XK_D)
//		ft_rotate(data, RIGHT);
//	else if (keycode == XK_W)
//		ft_rotate(data, UP);
//	else if (keycode == XK_S)
//		ft_rotate(data, DOWN);
//
	if (init_thread(data))
	{
		tmp = data->win;
		return (ft_clear_all(data->scene),
			mlx_destroy_display(data->mlx), free(data->mlx),
			free(tmp->gc), free(data->win), 1);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->mlx_img.img, 0, 0);
//	printf("Camera position : ");
//	print_vect(data->scene->camera->pos);
//	printf("Camera direction : ");
//	print_vect(data->scene->camera->look);
//	printf("\n");
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
