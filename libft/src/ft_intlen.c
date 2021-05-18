/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <smorel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:01:57 by smorel            #+#    #+#             */
/*   Updated: 2020/11/20 20:02:05 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen(int i)
{
	static size_t	len;

	len = 0;
	if (i == -2147483648)
		return (len = 11);
	if (i < 0)
	{
		len += 1;
		ft_intlen(-i);
	}
	if (i >= 10)
		ft_intlen(i / 10);
	len += 1;
	return (len);
}
