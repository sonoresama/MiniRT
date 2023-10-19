/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:08:09 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/09 18:08:26 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*res;
	size_t			i;
	size_t			size_t_size_max;

	size_t_size_max = ((size_t)-1);
	i = 0;
	if (nmemb == 0 || size == 0)
		return (ft_calloc(1, 1));
	if (size_t_size_max / size < nmemb)
		return (NULL);
	res = (unsigned char *)malloc(nmemb * size);
	if (res == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		res[i] = '\0';
		i++;
	}
	return ((void *)res);
}
