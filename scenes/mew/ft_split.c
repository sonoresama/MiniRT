/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eorer <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:00:37 by eorer             #+#    #+#             */
/*   Updated: 2023/11/20 16:59:53 by eorer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void  ft_free_tab(char **tab)
{
  int i;
  while(tab[i]) 
  {
    free(tab[i]);
    i++;
  }
  free(tab);
}

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset && charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_size_tab(char *str, char *charset)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (is_charset(*str, charset) == 0)
		{
			while ((is_charset(*str, charset) == 0) && *str)
				str++;
			count = count + 1;
		}
		else
			str++;
	}
	return (count);
}

static char	**ft_alloc(char *str, char *charset, char **tableau)
{
	int	count;
	int	i;

	count = 0;
	while (*str)
	{
		if (is_charset(*str, charset) == 0)
		{
			i = 0;
			while (is_charset(*str, charset) == 0 && *str)
			{
				i++;
				str++;
			}
			tableau[count] = malloc(i + 1);
			if (!tableau[count])
				return (NULL);
			count++;
		}
		else
			str++;
	}
	return (tableau);
}

static void	ft_implementation(char *str, char *charset, char **tableau)
{
	int	pos;
	int	i;
	int	j;

	pos = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_charset(str[i], charset) == 0)
		{
			j = 0;
			while (is_charset(str[i + j], charset) == 0 && str[i + j])
			{
				tableau[pos][j] = str[i + j];
				j++;
			}
			tableau[pos][j] = '\0';
			pos++;
			i = i + j;
		}
		else
			i++;
	}
}

char	**ft_split(const char *s, char *charset)
{
	char	**tableau;
	int		size;

	size = ft_size_tab((char *)s, charset);
	tableau = malloc(sizeof(tableau) * (size + 1));
	if (tableau == NULL)
		return (NULL);
	if (ft_alloc((char *)s, charset, tableau) == NULL)
	{
		ft_free_tab(tableau);
		return (NULL);
	}
	ft_implementation((char *)s, charset, tableau);
	tableau[size] = NULL;
	return (tableau);
}

/*int	main(void)
{
	char **tableau;
	int	i;
	char 	*str;
	char	*charset;

	i = 0;
	str = "HELLO JE SUIS \n TITO";
	charset = " \n";
	tableau = ft_split(str, charset);
	printf("%s\n", str);
	while (tableau[i])
	{
		printf("--> %s\n", tableau[i]);
		i++;
	}
	ft_free_tab(tableau);
	free(tableau);
	return (0);
}*/
