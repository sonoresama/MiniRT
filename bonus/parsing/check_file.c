/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:21:05 by blerouss          #+#    #+#             */
/*   Updated: 2023/12/04 14:08:36 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static int	ft_strstr_minirt(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j]
			&& little[j] && big[i + j])
			j++;
		if (little[j] == '\0' && big[i + j] == '\0')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_define_type(char **tab, t_scene *scene)
{
	static int	line = 0;

	line++;
	if (!tab[0])
		return (0);
	else if (tab[0][0] == 'A' && !tab[0][1] && ft_tablen(tab) == 3)
		return (ft_fill_atmos(tab, scene, line));
	else if (tab[0][0] == 'C' && !tab[0][1] && ft_tablen(tab) == 4)
		return (ft_fill_camera(tab, scene, line));
	else if ((tab[0][0] == 'l' || tab[0][0] == 'L')
				&& !tab[0][1] && ft_tablen(tab) == 4)
		return (ft_fill_light(tab, scene, line));
	else if (!ft_strncmp(tab[0], "sp", 3) && ft_tablen(tab) == 4)
		return (ft_fill_sphere(tab, scene, line));
	else if (!ft_strncmp(tab[0], "pl", 3) && ft_tablen(tab) == 4)
		return (ft_fill_plan(tab, scene, line));
	else if (!ft_strncmp(tab[0], "cy", 3) && ft_tablen(tab) == 6)
		return (ft_fill_cylinder(tab, scene, line));
	else if (!ft_strncmp(tab[0], "tr", 3) && ft_tablen(tab) == 5)
		return (ft_fill_triangle(tab, scene, line));
	else
		return (printf("%s%i\n", TYPE_ERR, line), 1);
}

int	check_file(int argc, char **argv, t_scene *scene)
{
	int		fd;
	char	*str;
	char	**tab;

	if (!scene)
		return (printf("%s", MAL_ERR));
	if (argc != 2 || ft_strstr_minirt(argv[1], ".rt"))
		return (printf("%s", ARG_ERR));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (printf("%s", OPEN_ERR));
	str = get_next_line(fd);
	while (str)
	{
		str[ft_strlen(str) - 1] = '\0';
		tab = ft_split_2_separator(str, ' ', '	');
		if (!tab)
			return (free(str), 1);
		if (ft_define_type(tab, scene))
			return (ft_clear_gnl(fd), free(str), ft_free_tab(tab), 1);
		ft_free_tab(tab);
		free(str);
		str = get_next_line(fd);
	}
	return (0);
}
