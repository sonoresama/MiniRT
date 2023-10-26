/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_plan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:20:00 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/26 14:32:19 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	ft_plan_add_back(t_plan *plan, t_scene *scene)
{
	t_plan	*tmp;

	if (!scene->plan)
		scene->plan = plan;
	else
	{
		tmp = scene->plan;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = plan;
	}
}

int	ft_fill_plan(char **tab, t_scene *scene, int line)
{
	char	**colors;
	t_plan	*tmp;

	tmp = ft_calloc(sizeof(t_plan), 1);
	if (!tmp)
		return (printf("%s", MAL_ERR), 1);
	if (ft_fill_vector(tab[1], &tmp->start, line))
		return (1);
	if (ft_fill_vector(tab[2], &tmp->vecteur, line)
		|| tmp->vecteur.x > 1 || tmp->vecteur.x < -1
		|| tmp->vecteur.y > 1 || tmp->vecteur.y < -1
		|| tmp->vecteur.z > 1 || tmp->vecteur.z < -1)
		return (1);
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
	ft_plan_add_back(tmp, scene);
	return (ft_free_tab(colors), 0);
}
