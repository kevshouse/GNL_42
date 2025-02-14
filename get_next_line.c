/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keanders <keanders@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:03:56 by keanders          #+#    #+#             */
/*   Updated: 2025/02/14 16:32:23 by keanders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char **buf, char *nl)
{
	char	*tmp;
	char	*line;
	size_t	len;

	len = nl - *buf + 1;
	line = ft_substr(*buf, 0, len);
	if (!line)
		return (NULL);
	tmp = ft_strdup(nl + 1);
	free(*buf);
	*buf = tmp;
	return (line);
}

ssize_t	read_from_fd(int fd, char *tmp_buf)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, tmp_buf, BUFFER_SIZE);
	if (bytes_read == -1)
		return (-1);
	tmp_buf[bytes_read] = '\0';
	return (bytes_read);
}

char	*update_buffer(char **buf, char *tmp_buf, ssize_t bytes_read)
{
	char	*new_buf;

	if (bytes_read <= 0)
		return (*buf);
	new_buf = ft_strjoin(*buf, tmp_buf);
	free(*buf);
	*buf = new_buf;
	if (!*buf)
		return (NULL);
	return (*buf);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*nl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup(""); // Initialize buffer if NULL
	tmp_buf = malloc(BUFFER_SIZE + 1);
	if (!tmp_buf)
		return (NULL);
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read_from_fd(fd, tmp_buf);
		if (bytes_read == -1)
		{
			free(tmp_buf);
			return (NULL);
		}
		buffer = update_buffer(&buffer, tmp_buf, bytes_read);
		if (!buffer || bytes_read == 0)
			break;
	}
	free(tmp_buf);
	if (!buffer)
		return (NULL);
	nl = ft_strchr(buffer, '\n');
	if (nl)
		return (extract_line(&buffer, nl));
	if (*buffer)
	{
		nl = ft_strdup(buffer);
		free(buffer);
		buffer = NULL;
		return (nl);
	}
	free(buffer);
	buffer = NULL;
	return (NULL);
}
