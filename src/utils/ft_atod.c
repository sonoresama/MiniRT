/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:31:01 by blerouss          #+#    #+#             */
/*   Updated: 2023/12/04 14:03:12 by blerouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static int	ft_longlen(long nb)
{
	int	i;

	i = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static int	ft_atod_after_separator(char **nptr, long resultat, float *res)
{
	long	diviseur;
	int		lengh;

	(*res) = (double)resultat;
	resultat = 0;
	diviseur = 10;
	if (**nptr)
		(*nptr)++;
	while (**nptr && ft_isdigit(**nptr))
	{
		resultat = resultat * 10 + **nptr - '0';
		(*nptr)++;
	}
	if (**nptr)
		return (1);
	lengh = ft_longlen(resultat);
	while (lengh-- > 1)
		diviseur *= 10;
	(*res) += (double)resultat / diviseur;
	return (0);
}

int	ft_atod(char *nptr, float *res)
{
	long	neg;
	long	resultat;

	resultat = 0;
	neg = 1;
	while ((*nptr >= 8 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
	{
		neg = -1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
	{
		resultat = resultat * 10 + *nptr - '0';
		nptr++;
	}
	if ((*nptr && *nptr != '.' ) || ((!*nptr || (*nptr) == '.')
			&& ft_atod_after_separator(&nptr, (long)resultat, res))
		|| *res > 1000 || *res < -1000)
		return (1);
	*res = *res * neg;
	return (0);
}
