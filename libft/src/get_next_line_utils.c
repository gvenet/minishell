/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <smorel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:39:47 by smorel            #+#    #+#             */
/*   Updated: 2020/12/04 17:24:39 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	glen(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] != c && str[len])
		len++;
	return (len);
}

void	gnl_free(char **str)
{
	free(*str);
	*str = NULL;
}
