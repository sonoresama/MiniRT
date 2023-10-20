/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:55:47 by eorer             #+#    #+#             */
/*   Updated: 2023/10/20 11:15:37 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	init_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_ui	mlx_get_pixel(t_imgs *img, int x, int y)
{
	return (*(unsigned int *)img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8)));
}

void	my_mlx_pixel_put(t_imgs *img, int x, int y, int color)
{
	char	*pixel;

	if (x > img->width || y > img->height)
		return ;
	if (x < 0 || y < 0)
		return ;
	pixel = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

void	init_img(t_imgs *img, void **mlx, int x, int y)
{
	img->img = mlx_new_image(*mlx, x, y);
	if (!img->img)
		return ;
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	if (!img->addr)
		return (free(img->img));
	img->width = x;
	img->height = y;
}
