/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:25:54 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/17 14:29:22 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_vect
{
	double	x;
	double	y;
	double	z;
}	t_vect;

typedef struct s_colors
{
	int	red;
	int	green;
	int	blue;
}	t_colors;

typedef struct s_atmos
{
	double		ratio;
	t_colors	colors;
}	t_atmos;

typedef struct s_camera
{
	t_vect	pos;
	t_vect	look;
	double	matrix[3][3];
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_vect		pos;
	double		ratio;
	t_colors	colors;
}	t_light;

typedef struct s_sphere
{
	t_vect			center;
	double			diameter;
	t_colors		colors;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_plan
{
	t_vect			start;
	t_vect			vecteur;
	t_colors		colors;
	struct s_plan	*next;
}	t_plan;

typedef struct s_cylinder
{
	t_vect				center;
	t_vect				vecteur;
	double				diameter;
	double				height;
	t_colors			colors;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_scene
{
	t_atmos		*atmos;
	t_camera	*camera;
	t_light		*light;
	t_sphere	*sphere;	
	t_plan		*plan;
	t_cylinder	*cylinder;
}	t_scene;

#endif
