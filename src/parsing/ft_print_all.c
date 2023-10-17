/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:03:21 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/17 12:03:24 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	ft_print_all(t_scene *scene)
{
	t_sphere	*start;
	t_plan		*start2;
	t_cylinder		*start3;

	start = scene->sphere;
	start2 = scene->plan;
	start3 = scene->cylinder;
	printf("atmos => ratio %.10f r %i g %i b %i\n", scene->atmos->ratio, scene->atmos->colors.red, scene->atmos->colors.green, scene->atmos->colors.blue);
	printf("camera => pos x %.10f y %.10f z %.10f\n	look x %.10f y %.10f z %.10f\n	fov %.10f\n", scene->camera->pos.x, scene->camera->pos.y, scene->camera->pos.z, scene->camera->look.x, scene->camera->look.y, scene->camera->look.z, scene->camera->fov);
	printf("light => pos x %.10f y %.10f z %.10f\n	ratio %.10f r %i g %i b %i\n", scene->light->pos.x, scene->light->pos.y, scene->light->pos.z, scene->light->ratio, scene->light->colors.red, scene->light->colors.green, scene->light->colors.blue);
	while (scene->sphere)
	{
		printf("sphere => pos x %.10f y %.10f z %.10f\n	diametre %.10f r %i g %i b %i\n", scene->sphere->center.x, scene->sphere->center.y, scene->sphere->center.z, scene->sphere->diameter, scene->sphere->colors.red, scene->sphere->colors.green, scene->sphere->colors.blue);
		scene->sphere = scene->sphere->next;
	}
	scene->sphere = start;
	while (scene->plan)
	{
		printf("plan => start x %.10f y %.10f z %.10f\n	vecteur x %.10f y %.10f z %.10f\n	 r %i g %i b %i\n", scene->plan->start.x, scene->plan->start.y, scene->plan->start.z, scene->plan->vecteur.x, scene->plan->vecteur.y, scene->plan->vecteur.z, scene->plan->colors.red, scene->plan->colors.green, scene->plan->colors.blue);
		scene->plan = scene->plan->next;
	}
	scene->plan = start2;
	while (scene->cylinder)
	{
		printf("cylinder => start x %.10f y %.10f z %.10f\n	diameter %.10f height %.10f\n	vecteur x %.10f y %.10f z %.10f\n	 r %i g %i b %i\n", scene->cylinder->center.x, scene->cylinder->center.y, scene->cylinder->center.z, scene->cylinder->diameter, scene->cylinder->height, scene->cylinder->vecteur.x, scene->cylinder->vecteur.y, scene->cylinder->vecteur.z, scene->cylinder->colors.red, scene->cylinder->colors.green, scene->cylinder->colors.blue);
		scene->cylinder = scene->cylinder->next;
	}
	scene->cylinder = start3;
}
