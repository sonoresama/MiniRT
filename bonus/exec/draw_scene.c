/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 14:58:09 by eorer             #+#    #+#             */
/*   Updated: 2023/11/23 14:01:18 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	get_sampled_color(t_colors color)
{
	int	r;
	int	g;
	int	b;

	r = color.red / SAMPLES_PER_PIXEL;
	g = color.green / SAMPLES_PER_PIXEL;
	b = color.blue / SAMPLES_PER_PIXEL;
	return (init_color(0, r, g, b));
}

static int	ray_throwing(t_data *data, int i, int j, t_colors *color)
{
	t_ray		ray;
	t_colors	r_color;

	ray = cast_ray(data, i, j);
	r_color = ray_color(data, ray);
	if (r_color.red == -1)
		return (-1);
	(*color) = add_colors((*color), r_color);
	return (0);
}

void	*b_draw_scene(void *tmp)
{
	int			j;
	int			s;
	t_thr_utils	*utils;
	t_colors	color;

	utils = (t_thr_utils *)tmp;
	while (utils->start < utils->max)
	{
		j = -1;
		while (++j < utils->data->img_height)
		{
			s = 0;
			color = new_color(0, 0, 0);
			while (s < SAMPLES_PER_PIXEL)
			{
				if (ray_throwing(utils->data, utils->start, j, &color) == -1)
					return (NULL);
				s++;
			}
			my_mlx_pixel_put(&utils->data->mlx_img, utils->start, j,
				get_sampled_color(color));
		}
		utils->start += NB_THREAD;
	}
	return (NULL);
}

static int	ft_fill_utils(t_thr_utils *utils, t_data *data)
{
	int	i;

	i = 0;
	while (i < NB_THREAD)
	{
		utils[i].start = i;
		utils[i].max = data->img_width;
		utils[i].data = data;
		i++;
	}
	return (0);
}

int	init_thread(t_data *data)
{
	pthread_t	*thread;
	t_thr_utils	utils[NB_THREAD];
	int			i;

	i = 0;
	thread = ft_calloc(sizeof(pthread_t), NB_THREAD);
	if (!thread)
		return (-1);
	ft_fill_utils(utils, data);
	while (i < NB_THREAD)
	{
		if (pthread_create(&thread[i], NULL, &b_draw_scene, (void *)&utils[i]))
		{
			while (i != -1)
				pthread_join(thread[i--], NULL);
			free(thread);
			return (-1);
		}
		i++;
	}
	while (i != 0)
		pthread_join(thread[--i], NULL);
	return (free(thread), 0);
}
