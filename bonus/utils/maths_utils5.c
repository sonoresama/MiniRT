/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:50:32 by blerouss          #+#    #+#             */
/*   Updated: 2023/12/01 13:50:53 by blerouss         ###   ########.fr       */
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
	x = cross(up, z);
	y = cross(z, x);
	return ((t_system){x, y, z});
}

int	ft_translate(t_system system, t_data *data, int keycode)
{
	if (keycode == XK_Right)
		data->scene->camera->pos.xyz -= system.x.xyz;
	else if (keycode == XK_Left)
		data->scene->camera->pos.xyz += system.x.xyz;
	else if (keycode == XK_Down)
		data->scene->camera->pos.xyz += system.z.xyz;
	else if (keycode == XK_Up)
		data->scene->camera->pos.xyz -= system.z.xyz;
	else if (keycode == XK_w)
		data->scene->camera->pos.y += 1;
	else if (keycode == XK_s)
		data->scene->camera->pos.y -= 1;
	else
		return (0);
	return (1);
}
