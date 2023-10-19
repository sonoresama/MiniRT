/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:46:03 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/16 16:16:14 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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
	return (0);
}
