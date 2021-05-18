/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <smorel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:01:57 by smorel            #+#    #+#             */
/*   Updated: 2020/12/05 10:23:42 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	stat_convert(int n, char *str, int rang)
{
	if (n >= 10)
		stat_convert(n / 10, str, rang - 1);
	str[rang] = (n % 10) + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		rang;
	size_t	ilen;

	ilen = ft_intlen(n);
	rang = 0;
	str = (char *)ft_memalloc(ilen + 1);
	if (!str)
		return (NULL);
	if (n == -2147483648)
		ft_strlcpy(str, "-2147483648", 12);
	else
	{
		if (n < 0)
		{
			n = -n;
			*str = '-';
			rang++;
		}
		stat_convert(n, str, ilen - 1);
	}
	return (str);
}
