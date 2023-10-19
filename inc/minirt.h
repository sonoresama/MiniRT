/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:12:14 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/19 11:45:15 by eorer            ###   ########.fr       */
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

//PARSING//

int		check_file(int argc, char **argv, t_scene *scene);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_atoi(const char *nptr, int *res);
int		ft_atod(char *nptr, double *res);
int		ft_fill_atmos(char **tab, t_scene *scene, int line);
int		ft_fill_camera(char **tab, t_scene *scene, int line);
int		ft_fill_cylinder(char **tab, t_scene *scene, int line);
int		ft_fill_light(char **tab, t_scene *scene, int line);
int		ft_fill_plan(char **tab, t_scene *scene, int line);
int		ft_fill_sphere(char **tab, t_scene *scene, int line);
int		ft_fill_vector(char *str, t_vect *vector, int line);
size_t	ft_strlen(const char *str);
char	**ft_split_2_separator(char const *str, char c, char d);
char	**ft_split(const char *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_free_tab(char **tab);
void	ft_clear_all(t_scene *scene);
void	ft_clear_gnl(int fd);
void	ft_print_all(t_scene *scene);

//EXEC//

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
