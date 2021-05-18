/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <smorel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 20:01:57 by smorel            #+#    #+#             */
/*   Updated: 2020/12/05 09:53:09 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	**ft_strdel_2d(char **t)
{
	int	i;

	i = -1;
	while (t[++i])
		;
	while (i--)
	{
		free(t[i]);
		t[i] = NULL;
	}
	free(t);
	return (NULL);
}
