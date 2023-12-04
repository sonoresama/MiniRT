/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:12:14 by blerouss          #+#    #+#             */
/*   Updated: 2023/12/04 14:07:49 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "get_next_line.h"
# include "define.h"
# include "structures.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <pthread.h>

//PARSING//

int			check_file(int argc, char **argv, t_scene *scene);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
int			ft_atoi(const char *nptr, int *res);
int			ft_atod(char *nptr, float *res);
int			ft_fill_atmos(char **tab, t_scene *scene, int line);
int			ft_fill_camera(char **tab, t_scene *scene, int line);
int			ft_fill_cylinder(char **tab, t_scene *scene, int line);
int			ft_fill_light(char **tab, t_scene *scene, int line);
int			ft_fill_plan(char **tab, t_scene *scene, int l);
int			ft_fill_sphere(char **tab, t_scene *scene, int l);
int			ft_fill_triangle(char **tab, t_scene *scene, int line);
int			ft_fill_vector(char *str, t_vect *vector, int line);
int			ft_init_data(t_data *data, t_scene *scene);
int			ft_count_separator(char *str, char separator);
int			parsing(t_data *data, int argc, char **argv);
size_t		ft_strlen(const char *str);
int			ft_tablen(char **tab);
char		**ft_split_2_separator(char const *str, char c, char d);
char		**ft_split(const char *s, char c);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_free_tab(char **tab);
void		ft_clear_all(t_scene *scene);
void		ft_clear_gnl(int fd);
void		ft_print_all(t_scene *scene);

//EXEC//

	/* Init */

	/* Sphere */
t_vect		v_normal_sphere(t_sphere sphere, t_vect hit_point);
t_vect		v_normal_plan(t_plan *plan);
void		get_closest_plan(t_ray ray, t_plan *plan, t_hit *first_hit_point);
void		get_closest_sphere(t_ray ray, t_sphere *sphere,
				t_hit *first_hit_point);
void		get_closest_cylinder(t_ray ray, t_cylinder *cylinder,
				t_hit *first_hit_point);
void		get_closest_triangle(t_ray ray, t_triangle *tr, t_hit *hit_point);
float		is_hiting_sphere(t_ray ray, t_sphere *sphere);
float		is_hiting_plan(t_ray ray, t_plan *plan);
int			is_hiting_object(t_data *data, t_ray ray);
float		is_hiting_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *hit);
int			is_hiting_triangle(t_ray ray, t_triangle *triangle,
				t_hit *hit_point);

	/*Scene*/
int			draw_scene(t_data *data);
void		*b_draw_scene(void *tmp);
t_colors	ray_color(t_data *data, t_ray ray);
t_colors	get_form_color(t_data *data, t_hit *hit_point, t_ray ray,
				t_light *light);
int			light_shadow(t_data *data, t_hit *hit_point, t_vect l_direction);
int			get_form_colors_sphere(float *t, t_sphere *sphere, t_hit *hit_point,
				t_vect l_direction);
int			get_form_colors_plan(float *t, t_plan *plan, t_hit *hit_point,
				t_vect l_direction);
t_colors	new_color(int red, int green, int blue);
t_vect		ft_atmos_intensity(t_atmos *atmos, t_hit *hit_point);
t_vect		ft_diffuse(t_light *light, t_vect l_direction, t_hit *hit_point,
				t_data *data);
t_vect		ft_specular(t_vect l_direction, t_hit *hit_point, t_ray ray,
				t_data *data);

	/*Ray*/
t_ray		new_ray(t_vect origin, t_vect direction);
t_ray		cast_ray(t_data *data, int i, int j);
t_vect		intersection(t_ray ray, float t);
t_vect		ft_light_intensity(t_light *light, float distance);
t_vect		ft_diffuse(t_light *light, t_vect l_direction, t_hit *hit_point,
				t_data *data);
t_vect		ft_atmos_intensity(t_atmos *atmos, t_hit *hit_point);
int			init_thread(t_data *data);

	/*Camera*/

// VECTORS UTILITIES //

float		ft_norm(t_vect vect);
t_vect		ft_normalize(t_vect vector);
t_vect		add_vectors(t_vect vect_a, t_vect vect_b);
t_colors	add_colors(t_colors ca, t_colors cb);
t_vect		sous_vectors(t_vect vect_a, t_vect vect_b);
t_vect		mult(t_vect vector, double c);
t_vect		mult_vect(t_vect vector, t_vect vector2);
t_vect		mult_mat_vect(float mat[4][4], t_vect vector);
double		dot(t_vect vect_a, t_vect vect_b);
t_vect		cross(t_vect a, t_vect b);
double		rad(double angle);
t_vect		new_vector(float x, float y, float z);
void		print_vect(t_vect vect);

t_system	init_system(t_camera *camera);
void		init_rot_matrix(float matrix[3][3], t_vect u, float angle);
t_vect		mat_rotate(float matrix[3][3], t_vect u);
t_system	init_system(t_camera *camera);
int			ft_translate(t_system system, t_data *data, int keycode);
t_vect		mat_rotate(float matrix[3][3], t_vect u);

// FONCTIONS MLX //

int			init_color(int t, int r, int g, int b);
t_ui		mlx_get_pixel(t_imgs *img, int x, int y);
void		my_mlx_pixel_put(t_imgs *img, int x, int y, int color);
void		init_img(t_imgs *img, void **mlx, int x, int y);
int			keypress(int keycode, t_data *data);
void		ft_bzero(void *s, size_t n);

#endif
