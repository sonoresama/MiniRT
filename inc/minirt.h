/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:12:14 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/17 14:29:54 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "get_next_line.h"
# include "define.h"
# include "struct.h"
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

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

#endif
