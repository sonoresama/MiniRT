/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:39:50 by eorer             #+#    #+#             */
/*   Updated: 2023/10/17 17:09:16 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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

	/*Objects *******************************************/
typedef struct	s_plan{
	t_vect	point;
	t_vect	direction;
	t_vect	color;
}	t_plan;

typedef	struct	s_sphere{
	t_vect	center;
	t_vect	color;
	int	radius;
	t_vect (*normal)(struct s_sphere, t_vect);
	struct s_sphere	*next;
}	t_sphere;

	/*Scene *******************************************/
typedef struct	s_hit_point{
	t_vect	point;
	int		type;
	float	t;
	void*	obj;
	t_vect	color;
}	t_hit_point;

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
	double	fov;
}	t_camera;

typedef	struct	s_a_light{
	float	intensity;
	t_vect	color;
}	t_a_light;

typedef struct s_lights{
	float	intensity;
	t_vect	coord;
	t_vect	color;
	struct s_lights *next;
}	t_lights;

	/* General *******************************************/
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_data {
	void	*mlx;
	void	*win;
	t_camera	camera;
	t_screen screen;
	t_hit_point	hit_point; //surement a tej
	t_sphere	*sphere;
	t_lights	*lights;
	t_img	mlx_img;
	int	img_width;
	int	img_height;
	int	fov;
	float	albedo;
}	t_data;

#endif
