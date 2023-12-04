/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:17:40 by blerouss          #+#    #+#             */
/*   Updated: 2023/12/04 14:07:26 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	ft_light_add_back(t_light *light, t_scene *scene)
{
	t_light	*tmp;

	if (!scene->light)
		scene->light = light;
	else
	{
		tmp = scene->light;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = light;
	}
}

int	ft_fill_light(char **tab, t_scene *scene, int line)
{
	char	**colors;
	t_light	*tmp;

	tmp = ft_calloc(sizeof(t_light), 1);
	if (!tmp)
		return (printf("%s", MAL_ERR), free(tmp), 1);
	if (ft_fill_vector(tab[1], &tmp->pos, line))
		return (printf("%s%i\n", POS_ERR, line), free(tmp), 1);
	if (ft_atod(tab[2], &tmp->ratio) || tmp->ratio < 0 || tmp->ratio > 1)
		return (printf("%s%i\n", RAT_ERR, line), free(tmp), 1);
	colors = ft_split(tab[3], ',');
	if (!colors)
		return (printf("%s", MAL_ERR), free(tmp), 1);
	if (ft_tablen(colors) != 3 || ft_count_separator(tab[3], ',') != 2
		|| ft_atoi(colors[0], &tmp->colors.red)
		|| ft_atoi(colors[1], &tmp->colors.green)
		|| ft_atoi(colors[2], &tmp->colors.blue)
		|| tmp->colors.red < 0 || tmp->colors.red > 255
		|| tmp->colors.green < 0 || tmp->colors.green > 255
		|| tmp->colors.blue < 0 || tmp->colors.blue > 255)
		return (ft_free_tab(colors), printf("%s%i\n", COL_ERR, line),
			free(tmp), 1);
	ft_light_add_back(tmp, scene);
	return (ft_free_tab(colors), 0);
}
