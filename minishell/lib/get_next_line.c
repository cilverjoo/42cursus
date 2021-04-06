/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 02:17:59 by heryu             #+#    #+#             */
/*   Updated: 2021/02/08 20:04:36 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	handle_error(char **rest)
{
	if (*rest != NULL)
	{
		free(*rest);
		*rest = NULL;
	}
	return (RET_ERROR);
}

static int	make_line(char **line, char **rest, char *newline_ptr)
{
	char		*tmp;
	size_t		line_size;
	size_t		rest_size;

	rest_size = ft_strlen(*rest);
	line_size = (newline_ptr == 0) ? rest_size : newline_ptr - *rest;
	if ((tmp = (char *)malloc((line_size + 1) * sizeof(char))) == NULL)
		return (handle_error(rest));
	ft_strncpy(tmp, *rest, line_size);
	tmp[line_size] = '\0';
	*line = tmp;
	if (newline_ptr == NULL)
	{
		free(*rest);
		*rest = NULL;
		return (RET_SUCCESS);
	}
	if ((tmp = (char *)malloc(rest_size - (line_size + 1) + 1)) == NULL)
		return (handle_error(rest));
	ft_strncpy(tmp, newline_ptr + 1, rest_size - (line_size + 1));
	tmp[rest_size - (line_size + 1)] = '\0';
	free(*rest);
	*rest = tmp;
	return (RET_SUCCESS);
}

static int	handle_eof(char **line, char **rest)
{
	char	*tmp;

	if (*rest == NULL)
	{
		if ((tmp = (char *)malloc(1 * sizeof(char))) == NULL)
			return (handle_error(rest));
		tmp[0] = '\0';
		*line = tmp;
	}
	else
		make_line(line, rest, NULL);
	return (RET_EOF);
}

int			get_next_line(int fd, char **line)
{
	static char		*rest[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	char			*newline_ptr;
	int				read_size;

	if (fd < 0 || fd >= OPEN_MAX || !line || BUFFER_SIZE <= 0)
		return (RET_ERROR);
	while ((newline_ptr = ft_my_strchr(rest[fd], '\n')) == NULL)
	{
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size <= 0)
			break ;
		buf[read_size] = '\0';
		if ((rest[fd] = ft_strncat_and_free(rest[fd], buf, read_size)) == 0)
			return (handle_error(&rest[fd]));
	}
	if (newline_ptr == NULL)
	{
		if (read_size == 0)
			return (handle_eof(line, &rest[fd]));
		if (read_size < 0)
			return (handle_error(&rest[fd]));
	}
	return (make_line(line, &rest[fd], newline_ptr));
}
