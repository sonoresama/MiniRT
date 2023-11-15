/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:50:26 by blerouss          #+#    #+#             */
/*   Updated: 2023/11/15 15:57:16 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	ft_clear_sphere(t_sphere *sphere)
{
	t_sphere	*tmp;

	while (sphere)
	{
		tmp = sphere->next;
		free(sphere);
		sphere = tmp;
	}
}

void	ft_clear_plan(t_plan *plan)
{
	t_plan	*tmp;

	while (plan)
	{
		tmp = plan->next;
		free(plan);
		plan = tmp;
	}
}

void	ft_clear_cylinder(t_cylinder *cylinder, t_triangle *triangle)
{
	t_cylinder	*tmp;
	t_triangle	*tmp2;

	while (cylinder)
	{
		tmp = cylinder->next;
		free(cylinder);
		cylinder = tmp;
	}
	while (triangle)
	{
		tmp2 = triangle->next;
		free(triangle);
		triangle = tmp2;
	}
}

void	ft_clear_light(t_light *light)
{
	t_light	*tmp;

	while (light)
	{
		tmp = light->next;
		free(light);
		light = tmp;
	}
}

void	ft_clear_all(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->atmos)
		free(scene->atmos);
	if (scene->camera)
		free(scene->camera);
	if (scene->light)
		ft_clear_light(scene->light);
	if (scene->sphere)
		ft_clear_sphere(scene->sphere);
	if (scene->plan)
		ft_clear_plan(scene->plan);
	if (scene->cylinder)
		ft_clear_cylinder(scene->cylinder, NULL);
	if (scene->triangle)
		ft_clear_cylinder(NULL, scene->triangle);
	if (scene)
		free(scene);
}
