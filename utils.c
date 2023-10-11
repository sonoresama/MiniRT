/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 18:19:22 by eorer             #+#    #+#             */
/*   Updated: 2023/09/26 11:42:51 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

//int	create_matrix(double, int x, int y)
//{
//	int	j;
//
//	j = 0;
//	matrix.x = x;
//	matrix.y = y;
//	matrix.mat = (int **)malloc(sizeof(int *) * y);
//	if (!matrix.mat)
//		return (1);
//	while (j < y) 
//	{
//		matrix.mat[j] = (int *)malloc(sizeof(int) * x);
//		if (!matrix.mat[j])
//			return (1);
//		j++;
//	}
//}
//
t_vect	new_vector(int x, int y, int z)
{
	t_vect	vect;

	vect.x = x;
	vect.y = y;
	vect.z = z;
	return (vect);
}
