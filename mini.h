/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:38:21 by eorer             #+#    #+#             */
/*   Updated: 2023/09/26 11:41:23 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

// MACROS //

// STRUCTURES //

typedef unsigned int	t_ui;

typedef struct	s_pixel{
	int	x;
	int	y;
}	t_pixel;

typedef struct	s_vect{
	double	x;
	double	y;
	double	z;
}	t_vect;

typedef struct	s_vect4{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_vect4;

typedef struct	s_ray{
	t_vect	origin;
	t_vect	direction;
}	t_ray;

typedef	struct	s_sphere{
	t_vect	center;
	t_vect	color;
	int	radius;
}	t_sphere;

typedef struct	s_screen{
	float	focal_length;//distance entre l'observateurice et le screen
	float	width;
	float	height;
	float	aspect_ratio;
}	t_screen;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_camera{
	t_vect	pos;
	t_vect	look;
	double	matrix[3][3];
	double	fov;
}	t_camera;

typedef struct s_data {
	void	*mlx;
	void	*win;
	t_screen screen;
	t_img	mlx_img;
	int	img_width;
	int	img_height;
	int	fov;
	t_camera	camera;
}	t_data;

// FONCTIONS PROGRAM //

void	draw_sphere(t_data *data, t_sphere *sphere);
void	generate_ray(t_ray *ray, t_data *data, t_pixel pixel);
t_vect	rotate_cam(double angle, char axis, t_vect vector);

// VECTORS UTILITIES //

void	ft_normalize(t_vect *vector);
t_vect	add_vectors(t_vect vect_a, t_vect vect_b);
t_vect	sous_vectors(t_vect vect_a, t_vect vect_b);
t_vect	mult_const_vector(t_vect vector, double c);
double	mult_vectors(t_vect vect_a, t_vect vect_b);
t_vect	cross_product(t_vect a, t_vect b);
double	rad(double angle);
t_vect	new_vector(int x, int y, int z);
void	print_vect(t_vect vect);

// FONCTIONS MLX //

int	init_color(int t, int r, int g, int b);
t_ui	mlx_get_pixel(t_img *img, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	init_img(t_img *img, void **mlx, int x, int y);

#endif
