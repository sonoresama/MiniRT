/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:17:40 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/16 16:37:04 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	ft_fill_light(char **tab, t_scene *scene, int line)
{
	char	**colors;

	if (scene->light)
		return (printf("%s", DTL_ERR), 1);
	scene->light = ft_calloc(sizeof(t_light), 1);
	if (!scene->light)
		return (printf("%s", MAL_ERR), 1);
	if (ft_fill_vector(tab[1], &scene->light->pos, line))
		return (1);
	if (ft_atod(tab[2], &scene->light->ratio) || scene->light->ratio < 0
		|| scene->light->ratio > 1)
		return (printf("%s%i\n", RAT_ERR, line), 1);
	colors = ft_split(tab[3], ',');
	if (!colors)
		return (printf("%s", MAL_ERR), 1);
	if (ft_atoi(colors[0], &scene->light->colors.red)
		|| ft_atoi(colors[1], &scene->light->colors.green)
		|| ft_atoi(colors[2], &scene->light->colors.blue)
		|| scene->light->colors.red < 0 || scene->light->colors.red > 255
		|| scene->light->colors.green < 0 || scene->light->colors.green > 255
		|| scene->light->colors.blue < 0 || scene->light->colors.blue > 255)
		return (ft_free_tab(colors), printf("%s%i\n", COL_ERR, line), 1);
	ft_free_tab(colors);
	return (0);
}
