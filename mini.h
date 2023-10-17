/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:38:21 by eorer             #+#    #+#             */
/*   Updated: 2023/10/17 13:41:13 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"
# include "structures.h"

// MACROS //

# define WIDTH 1600
# define HEIGHT 900 
# define SAMPLES_PER_PIXEL 1 
# define MAX_DEPTH 1
# define SPHERE 10
# define PLAN 11
# define CYLINDRE 12
# define BACKGROUND 13

// FONCTIONS PROGRAM //

	/* Init */
int	init_data(t_data *data);

	/* Sphere */
//void	is_hiting_sphere(t_ray ray, t_sphere sphere, t_vect **hit_point);
float	is_hiting_sphere(t_ray ray, t_sphere sphere);
float	is_hiting_plan(t_ray ray, t_data *data);
float	get_closest_sphere(t_ray ray, t_data *data, t_hit_point *hit_point);
t_vect	v_normal_sphere(t_sphere sphere, t_vect hit_point);

	/*Image*/
void	draw_scene(t_data *data);
t_vect	get_color(t_ray ray, t_data *data, int depth, t_vect prev_color);
int		get_sampled_color(t_vect color);
t_hit_point	set_closest_obj(t_ray ray, t_data *data);
t_vect	get_sphere_color(t_hit_point hit_point);

	/*Ray*/
t_ray	generate_ray(t_data *data, t_pixel pixel);
t_ray	new_ray(t_vect origin, t_vect direction);

	/*Camera*/
void	generate_rot_matrix(t_data *data);
t_vect	camera_to_world(double matrix[3][3], t_vect *vector, t_vect dest);
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
