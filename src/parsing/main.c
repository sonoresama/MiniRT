/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:10:50 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/17 12:35:31 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	main(int argc, char **argv)
{
	t_scene	*scene;

	scene = ft_calloc(sizeof(t_scene), 1);
	if (check_file(argc, argv, scene))
		return (ft_clear_all(scene), 1);
//	data_init(&data);
//	img_loop(&data);
//	ft_lstclear_fdf(&data.save);
//	end_window(&data);
	ft_print_all(scene);
	ft_clear_all(scene);
	return (0);
}
