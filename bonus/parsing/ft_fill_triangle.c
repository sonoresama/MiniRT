/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_triangle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:33:44 by blerouss          #+#    #+#             */
/*   Updated: 2023/12/04 16:11:32 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	ft_triangle_add_back(t_triangle *triangle, t_scene *scene)
{
	t_triangle	*tmp;

	if (!scene->triangle)
		scene->triangle = triangle;
	else
	{
		tmp = scene->triangle;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = triangle;
	}
}

static int	ft_fill_colors(char *str, t_triangle *tmp, int line)
{
	char	**colors;

	colors = ft_split(str, ',');
	if (!colors)
		return (printf("%s", MAL_ERR), 1);
	if (ft_tablen(colors) != 3 || ft_count_separator(str, ',') != 2
		|| ft_atoi(colors[0], &tmp->colors.red)
		|| ft_atoi(colors[1], &tmp->colors.green)
		|| ft_atoi(colors[2], &tmp->colors.blue)
		|| tmp->colors.red < 0 || tmp->colors.red > 255
		|| tmp->colors.green < 0 || tmp->colors.green > 255
		|| tmp->colors.blue < 0 || tmp->colors.blue > 255)
		return (ft_free_tab(colors), printf("%s%i\n", COL_ERR, line), 1);
	return (ft_free_tab(colors), 0);
}

int	ft_fill_triangle(char **tab, t_scene *scene, int line)
{
	t_triangle	*tmp;

	tmp = ft_calloc(sizeof(t_triangle), 1);
	if (!tmp)
		return (printf("%s", MAL_ERR), free(tmp), 1);
	if (ft_fill_vector(tab[1], &tmp->a, line))
		return (printf("%s%i\n", POS_ERR, line), free(tmp), 1);
	if (ft_fill_vector(tab[2], &tmp->b, line))
		return (printf("%s%i\n", POS_ERR, line), free(tmp), 1);
	if (ft_fill_vector(tab[3], &tmp->c, line))
		return (printf("%s%i\n", POS_ERR, line), free(tmp), 1);
	if (ft_fill_colors(tab[4], tmp, line))
		return (free(tmp), 1);
	ft_triangle_add_back(tmp, scene);
	return (0);
}
