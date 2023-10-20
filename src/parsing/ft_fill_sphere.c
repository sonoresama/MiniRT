/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:47:44 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/20 17:00:41 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	ft_sphere_add_back(t_sphere *sphere, t_scene *scene)
{
	t_sphere	*tmp;

	if (!scene->sphere)
		scene->sphere = sphere;
	else
	{
		tmp = scene->sphere;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = sphere;
	}
}

int	ft_fill_sphere(char **tab, t_scene *scene, int line)
{
	char		**colors;
	t_sphere	*tmp;

	tmp = ft_calloc(sizeof(t_sphere), 1);
	if (ft_fill_vector(tab[1], &tmp->center, line))
		return (1);
	if (ft_atod(tab[2], &tmp->radius) || tmp->radius <= 0)
		return (printf("%s%i\n", DIA_ERR, line), 1);
	colors = ft_split(tab[3], ',');
	if (!colors)
		return (printf("%s", MAL_ERR), 1);
	if (ft_atoi(colors[0], &tmp->colors.red)
		|| ft_atoi(colors[1], &tmp->colors.green)
		|| ft_atoi(colors[2], &tmp->colors.blue)
		|| tmp->colors.red < 0 || tmp->colors.red > 255
		|| tmp->colors.green < 0 || tmp->colors.green > 255
		|| tmp->colors.blue < 0 || tmp->colors.blue > 255)
		return (ft_free_tab(colors), printf("%s%i\n", COL_ERR, line), 1);
	tmp->normal = &v_normal_sphere;
	ft_sphere_add_back(tmp, scene);
	return (ft_free_tab(colors), 0);
}
