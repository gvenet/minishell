/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <smorel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:01:57 by smorel            #+#    #+#             */
/*   Updated: 2020/12/05 10:25:18 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new;
	char	*n;
	int		i;

	if (!s || !f)
		return (NULL);
	new = (char *)ft_memalloc(ft_strlen(s) + 1);
	if (!(new))
		return (NULL);
	n = new;
	i = 0;
	while (*s)
		*n++ = f(i++, *s++);
	return (new);
}
