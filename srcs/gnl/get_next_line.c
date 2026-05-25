/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgil--de <sgil--de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:15:59 by sgil--de          #+#    #+#             */
/*   Updated: 2026/05/25 00:00:00 by sgil--de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_free(char *buf, char *add)
{
	char	*joined;

	joined = ft_strjoin(buf, add);
	free(buf);
	return (joined);
}

static char	*read_to_newline(int fd, char *buf)
{
	char	temp[BUFFER_SIZE + 1];
	ssize_t	bytes;

	bytes = 1;
	while (!ft_strchr(buf, '\n') && bytes > 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buf), NULL);
		temp[bytes] = '\0';
		buf = join_free(buf, temp);
		if (!buf)
			return (NULL);
	}
	return (buf);
}

static char	*split_line(char *buf, char *rest)
{
	char	*newline;

	newline = ft_strchr(buf, '\n');
	if (newline)
	{
		ft_strlcpy(rest, newline + 1, BUFFER_SIZE + 1);
		*(newline + 1) = '\0';
	}
	if (!*buf)
		return (free(buf), NULL);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	rest[FD_MAX][BUFFER_SIZE + 1];
	char		*buf;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buf = ft_strdup(rest[fd]);
	rest[fd][0] = '\0';
	if (!buf)
		return (NULL);
	buf = read_to_newline(fd, buf);
	if (!buf)
		return (NULL);
	return (split_line(buf, rest[fd]));
}
