/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <smorel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:01:57 by smorel            #+#    #+#             */
/*   Updated: 2020/12/05 10:22:38 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *s1, const char *s2)
{
	char	*s;

	s = s1;
	s1 = &s1[ft_strlen(s1)];
	while (*s2)
		*s1++ = *s2++;
	*s1 = '\0';
	return (s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	size_join;

	if (!s1 || !s2)
		return (NULL);
	size_join = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)ft_memalloc(size_join + 1);
	if (!join || !s1 || !s2)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	return (ft_strcat(join, s2));
}
