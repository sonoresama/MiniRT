/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_atmos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:40:41 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/16 14:55:48 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	ft_fill_atmos(char **tab, t_scene *scene, int line)
{
	char	**colors;

	if (scene->atmos)
		return (printf("%s", DTA_ERR), 1);
	scene->atmos = ft_calloc(sizeof(t_atmos), 1);
	if (!scene->atmos)
		return (printf("%s", MAL_ERR), 1);
	ft_atod(tab[1], &scene->atmos->ratio);
	colors = ft_split(tab[2], ',');
	if (!colors)
		return (printf("%s", MAL_ERR), 1);
	if (ft_atoi(colors[0], &scene->atmos->colors.red)
		|| ft_atoi(colors[1], &scene->atmos->colors.green)
		|| ft_atoi(colors[2], &scene->atmos->colors.blue)
		|| scene->atmos->colors.red < 0 || scene->atmos->colors.red > 255
		|| scene->atmos->colors.green < 0 || scene->atmos->colors.green > 255
		|| scene->atmos->colors.blue < 0 || scene->atmos->colors.blue > 255)
		return (ft_free_tab(colors), printf("%s%i\n", COL_ERR, line), 1);
	ft_free_tab(colors);
	return (0);
}
