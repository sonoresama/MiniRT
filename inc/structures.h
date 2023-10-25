/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:39:50 by eorer             #+#    #+#             */
/*   Updated: 2023/10/20 17:43:51 by bastien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../minilibx-linux/mlx_int.h"

// STRUCTURES //

typedef unsigned int	t_ui;

	/*Utilities *******************************************/
typedef struct	s_pixel{
	int	x;
	int	y;
}	t_pixel;

typedef struct	s_vect{
	float	x;
	float	y;
	float	z;
}	t_vect;

typedef struct s_colors
{
	int	red;
	int	green;
	int	blue;
}	t_colors;

typedef struct	s_ray{
	t_vect	origin;
	t_vect	direction;
}	t_ray;

typedef struct	s_hit{
	t_vect	point;
	t_colors	color;
	t_vect	normal;
	void*	obj;
	int	type;
	float	time;
}	t_hit;

	/*Objects ********************************************/
typedef struct s_plan
{
	t_vect			start;
	t_vect			vecteur;
	t_colors		colors;
	t_vect (*normal)(struct s_plan, t_vect);
	struct s_plan	*next;
}	t_plan;

typedef	struct	s_sphere{
	t_vect	center;
	t_colors	colors;
	float	diameter;
	t_vect (*normal)(struct s_sphere, t_vect);
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_cylinder
{
	t_vect				center;
	t_vect				vecteur;
	float				diameter;
	float				height;
	t_colors			colors;
	t_vect (*normal)(struct s_cylinder, t_vect);
	struct s_cylinder	*next;
}	t_cylinder;

	/*Scene **********************************************/

typedef struct	s_screen{
	float	focal_length;//distance entre l'observateurice et le screen
	float	width;
	float	height;
	float	aspect_ratio;
}	t_screen;

typedef struct s_camera{
	t_vect	pos;
	t_vect	look;
	double	matrix[3][3];
	float	fov;
}	t_camera;

typedef struct s_atmos
{
	float		ratio;
	t_colors	colors;
}	t_atmos;

typedef struct s_light
{
	t_vect		pos;
	float		ratio;
	t_colors	colors;
	struct	s_light	*next;
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
	float	albedo;
}	t_scene;

typedef struct s_data {
	void	*mlx;
	void	*win;
	t_scene	*scene;
	t_screen screen;
	t_sphere	*sphere;
	t_imgs	mlx_img;
	int	img_width;
	int	img_height;
	int	count;
	int	error;
}	t_data;

#endif
