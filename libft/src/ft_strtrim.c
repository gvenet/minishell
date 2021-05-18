/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <smorel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:01:57 by smorel            #+#    #+#             */
/*   Updated: 2020/12/05 10:23:09 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *c)
{
	char	*trim;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	trim = (char *)&s[len - 1];
	while (ft_strchr(c, *trim--) && len)
		len--;
	trim = (char *)s;
	while (ft_strchr(c, *trim++) && len)
		len--;
	trim = (char *)ft_memalloc(len + 1);
	if (!(trim))
		return (NULL);
	while (ft_strchr(c, *s))
		s++;
	return (ft_strncpy(trim, s, len));
}
