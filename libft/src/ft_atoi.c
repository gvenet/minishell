/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <smorel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:01:57 by smorel            #+#    #+#             */
/*   Updated: 2020/12/05 09:09:55 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoi(const char *nptr)
{
	long long int	val;
	int				signe;

	signe = 1;
	val = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\f' || *nptr == '\n' \
		 || *nptr == '\r' || *nptr == '\v')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signe = -signe;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
		val = 10 * val + (*nptr++ - '0');
	return (signe * val);
}
