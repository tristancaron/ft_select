/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 10:58:38 by tcaron            #+#    #+#             */
/*   Updated: 2013/11/21 10:58:39 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int			ft_strsplit_alloc(char const *s, int nbr_of_word, char **result,
								char c);
void		ft_strsplit_write(char const *s, int nbr_of_word, char **result,
								char c);
int			ft_strsplit_nb_word(char const *s, char c);

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	char	**result;
	int		nbr_of_word;

	if (!s)
		return (NULL);
	i = 0;
	nbr_of_word = ft_strsplit_nb_word(s, c);
	result = (char **)malloc(sizeof(char *) * (nbr_of_word + 1));
	if (!result)
		return (NULL);
	if (ft_strsplit_alloc(s, nbr_of_word, result, c) == 0)
		return (NULL);
	ft_strsplit_write(s, nbr_of_word, result, c);
	return (result);
}

int			ft_strsplit_alloc(char const *s, int nbr_of_word, char **result,
								char c)
{
	int		i;
	int		nbr_of_letter;
	int		s_nbr_of_word;

	i = 0;
	s_nbr_of_word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
			{
				nbr_of_letter++;
				i++;
			}
			result[s_nbr_of_word] = (char *)malloc(sizeof(char)
													* (nbr_of_letter + 1));
			if (!result[s_nbr_of_word])
				return (0);
			s_nbr_of_word += (s_nbr_of_word < nbr_of_word) ? 1 : 0;
			nbr_of_letter = 0;
		}
		i++;
	}
	return (1);
}

void		ft_strsplit_write(char const *s, int nbr_of_word, char **result,
								char c)
{
	int		i;
	int		nbr_of_letter;
	int		s_nbr_of_word;

	i = 0;
	s_nbr_of_word = 0;
	nbr_of_letter = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
			{
				result[s_nbr_of_word][nbr_of_letter] = s[i];
				i++;
				nbr_of_letter++;
			}
			result[s_nbr_of_word][nbr_of_letter] = '\0';
			s_nbr_of_word += (s_nbr_of_word < nbr_of_word) ? 1 : 0;
			nbr_of_letter = 0;
		}
		i++;
	}
	result[s_nbr_of_word] = NULL;
}

int			ft_strsplit_nb_word(char const *s, char c)
{
	int		i;
	int		nbr_of_word;

	i = 0;
	nbr_of_word = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
			{
				i++;
			}
			nbr_of_word += 1;
		}
		i += (s[i] != '\0') ? 1 : 0;
	}
	return (nbr_of_word);
}
