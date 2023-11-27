/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:56:44 by bastien           #+#    #+#             */
/*   Updated: 2023/11/27 17:52:27 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parsing(t_data *data, int argc, char **argv)
{
	t_scene		*scene;
	t_win_list	*tmp;

	scene = ft_calloc(sizeof(t_scene), 1);
	if (check_file(argc, argv, scene))
		return (ft_clear_all(scene), 1);
	if (!scene->atmos)
		return (ft_clear_all(scene), printf("%s", ARG_ERR), 1);
	if (!scene->camera)
		return (ft_clear_all(scene), printf("%s", ARG_ERR), 1);
	if (ft_init_data(data, scene))
		return (ft_clear_all(scene), 1);
	if (draw_scene(data))
	{
		tmp = data->win;
		return (ft_clear_all(scene),
			mlx_destroy_display(data->mlx), free(data->mlx),
			free(tmp->gc), free(data->win), 1);
	}
	return (0);
}
