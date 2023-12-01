/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:59:22 by bastien           #+#    #+#             */
/*   Updated: 2023/12/01 14:38:37 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../minilibx-linux/mlx_int.h"

// STRUCTURES //

typedef unsigned int	t_ui;

	/*Utilities *******************************************/
typedef struct s_pixel{
	int	x;
	int	y;
}	t_pixel;

typedef float			t_vect	__attribute__((ext_vector_type(3)));

typedef struct s_system{
	t_vect	x;
	t_vect	y;
	t_vect	z;
}	t_system;

typedef struct s_colors
{
	int	red;
	int	green;
	int	blue;
}	t_colors;

typedef struct s_ray{
	t_vect	origin;
	t_vect	direction;
}	t_ray;

typedef struct s_hit{
	t_vect		point;
	t_colors	color;
	t_vect		normal;
	void		*obj;
	int			type;
	float		time;
}	t_hit;

	/*Objects ********************************************/

typedef struct s_plan
{
	t_vect			start;
	t_vect			vecteur;
	t_colors		colors;
	struct s_plan	*next;
}	t_plan;

typedef struct s_sphere{
	t_vect			center;
	t_colors		colors;
	float			diameter;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_triangle
{
	t_vect				a;
	t_vect				b;
	t_vect				c;
	t_colors			colors;
	struct s_triangle	*next;
}	t_triangle;

typedef struct s_cylinder
{
	t_vect				center;
	t_vect				vecteur;
	float				diameter;
	float				height;
	t_colors			colors;
	struct s_cylinder	*next;
}	t_cylinder;

	/*Scene **********************************************/

typedef struct s_screen{
	float	focal_length;
	float	width;
	float	height;
	float	aspect_ratio;
}	t_screen;

typedef struct s_camera{
	t_vect	pos;
	t_vect	look;
	float	matrix[4][4];
	float	fov;
	float	scale;
}	t_camera;

typedef struct s_atmos
{
	float		ratio;
	t_colors	colors;
}	t_atmos;

typedef struct s_light
{
	t_vect			pos;
	float			ratio;
	t_colors		colors;
	struct s_light	*next;
}	t_light;

	/* General *******************************************/
typedef struct s_imgs {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_imgs;

typedef struct s_scene
{
	t_atmos		*atmos;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;	
	t_plan		*plan;
	t_cylinder	*cylinder;
	t_triangle	*triangle;
	float		albedo;
}	t_scene;

typedef struct s_data {
	void		*mlx;
	void		*win;
	t_scene		*scene;
	t_screen	screen;
	t_sphere	*sphere;
	t_imgs		mlx_img;
	int			img_width;
	int			img_height;
	int			error;
}	t_data;

typedef struct s_thr_utils
{
	int				max;
	int				start;
	t_data			*data;
}	t_thr_utils;

#endif
