/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_msh2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvenet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:29:16 by gvenet            #+#    #+#             */
/*   Updated: 2021/03/16 14:29:23 by gvenet           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_sep(char c)
{
	if (c == ';' || c == '|')
		return (1);
	return (0);
}

int	is_quot(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

char	*trim_ws(char *buf)
{
	while (*buf == ' ' && *buf)
		buf++;
	return (buf);
}

int	is_bckslash(char **buf)
{
	if (**buf == '\\')
	{
		(*buf)++;
		if (**buf == 0)
			return (E_FAIL);
	}
	return (E_SUCCESS);
}

char	*file_path(char *path)
{
	if (*path != '/')
		return (ft_strjoin("./", path));
	else
		return (ft_strjoin("", path));
}
