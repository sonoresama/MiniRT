/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blerouss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:23:49 by blerouss          #+#    #+#             */
/*   Updated: 2023/10/27 15:15:58 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define ARG_ERR "Error\nNécessite une description de scène dans un \
fichier .rt en premier argument\n" 
# define OPEN_ERR "Error\nProblème rencontré lors de l'ouverture du fichier .rt\n"
# define MAL_ERR "Error\nEchec d'allocation mémoire\n"
# define TYPE_ERR "Error\nProblème pendant l'analyse du fichier .rt, \
type inconnu sur la ligne "
# define DTA_ERR "Error\nLes informations de l'ambiance sont déclarées \
plusieurs fois\n"
# define DTC_ERR "Error\nLes informations de la caméra sont déclarées \
plusieurs fois\n"
# define DTL_ERR "Error\nLes informations de la lumière sont déclarées \
plusieurs fois\n"
# define COL_ERR "Error\nMauvaise déclaration des couleurs RGB à la ligne "
# define FOV_ERR "Error\nMauvaise déclaration du FOV de la caméra à la ligne "
# define POS_ERR "Error\nMauvaise déclaration des coordonnées à la ligne "
# define RAT_ERR "Error\nMauvaise déclaration du ratio de luminosité à la ligne "
# define DIA_ERR "Error\nMauvaise déclaration du diamètre à la ligne "
# define HEI_ERR "Error\nMauvaise déclaration de la hauteur à la ligne "
# define MLX_ERR "Error\nProbleme lors de l'utilisation des fonctions de la mlx\n"

// MACROS //

# define WIDTH 1600
# define HEIGHT 900 
# define SAMPLES_PER_PIXEL 1
# define MAX_DEPTH 1
# define SPHERE 10
# define PLAN 11
# define CYLINDRE 12
# define BACKGROUND 13
# define MALLOC_ERR 100

// COLOR PRINT //

# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"

// OTHER //

# define ABS(x) x < 0 ? -1 * x : x

#endif
