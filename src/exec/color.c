/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:23:18 by eorer             #+#    #+#             */
/*   Updated: 2023/10/19 18:22:11 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	ray_color(t_data *data, t_ray ray)
{
	int	i;

	i = is_hiting_sphere(ray, data->scene->sphere);
	if (i == -1)
		return (-1);
	else if (i == 1)
		return(init_color(0, 155, 155, 155));
	return (init_color(0, 0, 0, 0));
}
