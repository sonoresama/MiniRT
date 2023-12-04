/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cylinder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:31:49 by blerouss          #+#    #+#             */
/*   Updated: 2023/12/04 15:55:48 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	ft_cylinder_add_back(t_cylinder *cylinder, t_scene *scene)
{
	t_cylinder	*tmp;

	if (!scene->cylinder)
		scene->cylinder = cylinder;
	else
	{
		tmp = scene->cylinder;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = cylinder;
	}
}

static int	ft_fill_colors(char *str, t_cylinder *tmp, int line)
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

int	ft_fill_cylinder(char **tab, t_scene *scene, int line)
{
	t_cylinder	*tmp;

	tmp = ft_calloc(sizeof(t_cylinder), 1);
	if (!tmp)
		return (printf("%s", MAL_ERR), free(tmp), 1);
	if (ft_fill_vector(tab[1], &tmp->center, line))
		return (printf("%s%i\n", POS_ERR, line), free(tmp), 1);
	if (ft_fill_vector(tab[2], &tmp->vecteur, line)
		|| tmp->vecteur.x > 1 || tmp->vecteur.x < -1
		|| tmp->vecteur.y > 1 || tmp->vecteur.y < -1
		|| tmp->vecteur.z > 1 || tmp->vecteur.z < -1)
		return (printf("%s%i\n", VEC_ERR, line), free(tmp), 1);
	if (ft_atod(tab[3], &tmp->diameter) || tmp->diameter <= 0)
		return (printf("%s%i\n", DIA_ERR, line), free(tmp), 1);
	if (ft_atod(tab[4], &tmp->height) || tmp->height <= 0)
		return (printf("%s%i\n", HEI_ERR, line), free(tmp), 1);
	if (ft_fill_colors(tab[5], tmp, line))
		return (free(tmp), 1);
	tmp->vecteur = ft_normalize(tmp->vecteur);
	ft_cylinder_add_back(tmp, scene);
	return (0);
}
