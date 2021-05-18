/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <smorel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:01:57 by smorel            #+#    #+#             */
/*   Updated: 2020/12/05 09:50:09 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	normi_power(char **split, int i, int word_len, const char *word)
{
	split[i] = ft_substr(word, 0, word_len);
	if (!split[i])
		ft_strdel_2d(split);
}

static char	**stat_algo(char **split, char const *s, char c, int i)
{
	int			word_len;
	char const	*word;

	while (ft_countwords(s, c))
	{
		while (*s == c)
			s++;
		if (*s != c)
		{
			word_len = 0;
			word = s;
		}
		while (*s != c && *s != '\0')
		{
			word_len++;
			s++;
		}
		if (word_len)
			normi_power(split, i, word_len, word);
		i++;
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (!split)
		return (NULL);
	stat_algo(split, s, c, 0);
	return (split);
}
