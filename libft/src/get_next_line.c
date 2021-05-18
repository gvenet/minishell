/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smorel <smorel@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:02:02 by smorel            #+#    #+#             */
/*   Updated: 2020/12/04 16:14:38 by smorel           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_rea(char *ptr, int size)
{
	char	*nptr;
	int		i;

	nptr = (char *)malloc(sizeof(char) * size);
	if (!nptr)
	{
		gnl_free(&ptr);
		return (NULL);
	}
	i = 0;
	while (size-- > 1 && ptr[i])
	{
		nptr[i] = ptr[i];
		i++;
	}
	nptr[i] = '\0';
	gnl_free(&ptr);
	return (nptr);
}

static int	check_kept(char *to_keep, char **line)
{
	char	*kept;
	char	*tmp;
	int		in_line;

	kept = to_keep;
	*line = gnl_rea(*line, glen(to_keep, '\n') + 1);
	if (!(*line))
		return (-1);
	tmp = *line;
	in_line = 2;
	while (*kept)
	{
		if (*kept == '\n' && in_line == 2)
		{
			in_line = 1;
			*tmp = '\0';
			kept++;
			tmp = to_keep;
		}
		*tmp++ = *kept++;
	}
	*tmp = '\0';
	return (in_line);
}

static int	clean_buf(char **buf, char **to_keep, char **line, int ret)
{
	char	*tmp;
	char	*buffer;
	int		in_line;

	in_line = 2;
	buffer = *buf;
	*line = gnl_rea(*line, glen(*line, '\0') + ret + 1);
	*to_keep = gnl_rea(*to_keep, glen(*to_keep, '\0') + ret + 1);
	if (!(*line) || !(*to_keep))
		return (-1);
	tmp = &(*line)[glen(*line, '\0')];
	while (ret--)
	{
		if (*buffer == '\n' && in_line == 2)
		{
			*tmp = '\0';
			buffer++;
			in_line = 1;
			tmp = *to_keep;
		}
		*tmp++ = *buffer++;
	}
	*tmp = '\0';
	return (in_line);
}

static int	gnl_algo(int in_line, int fd, char **to_keep, char **line)
{
	int			ret;
	char		*buf;

	while (in_line > 1)
	{
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (-1);
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (-1);
		buf[ret] = '\0';
		if (ret < 1)
			in_line = ret;
		else
			in_line = clean_buf(&buf, to_keep, line, ret);
		gnl_free(&buf);
	}
	*line = gnl_rea(*line, glen(*line, '\0') + 1);
	if (!(*line))
		return (-1);
	return (in_line);
}

int	get_next_line(int fd, char **line)
{
	static char	*to_keep[4096];
	int			in_line;

	if (BUFFER_SIZE < 1 || !line || read(fd, to_keep, 0) < 0)
		return (-1);
	*line = (char *)malloc(sizeof(char) * 1);
	if (!(*line))
		return (-1);
	**line = '\0';
	in_line = 2;
	if (to_keep[fd])
		in_line = check_kept(to_keep[fd], line);
	else
	{
		to_keep[fd] = (char *)malloc(sizeof(char) * 1);
		if (!to_keep[fd])
			return (-1);
		*to_keep[fd] = '\0';
	}
	in_line = gnl_algo(in_line, fd, &to_keep[fd], line);
	if (in_line != 0 && in_line != 1)
		return (-1);
	if (!in_line)
		gnl_free(&to_keep[fd]);
	return (in_line);
}
