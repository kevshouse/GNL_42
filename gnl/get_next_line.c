//get_next_line.c

#include "get_next_line.h"

static char	*extract_line(char **static_buffer)
{
	char	*newline_ptr;
	char	*line;
	char	*remaining;

	newline_ptr = ft_strchr(*static_buffer, '\n');
	if (!newline_ptr)
		return (NULL);
	line = malloc(newline_ptr - *static_buffer + 2);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *static_buffer, newline_ptr - *static_buffer + 2);
	remaining = NULL;
	if (*(newline_ptr + 1) != '\0')
		remaining = ft_strdup(newline_ptr + 1);
	free(*static_buffer);
	*static_buffer = remaining;
	return (line);
}

static char	*read_buffer(int fd, char *static_buffer)
{
	char	*temp_buffer;
	ssize_t	bytes_read;

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp_buffer);
		if (bytes_read == 0)
			return (static_buffer);
		return (NULL);
	}
	temp_buffer[bytes_read] = '\0';
	return (ft_strjoin_free(static_buffer, temp_buffer));
}

char	*get_next_line(int fd)
{
	static char	*static_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = extract_line(&static_buffer);
	if (line)
		return (line);
	static_buffer = read_buffer(fd, static_buffer);
	if (!static_buffer)
		return (NULL);
	while (!ft_strchr(static_buffer, '\n'))
	{
		static_buffer = read_buffer(fd, static_buffer);
		if (!static_buffer)
			break ;
	}
	line = extract_line(&static_buffer);
	if (!line && static_buffer)
	{
		line = static_buffer;
		static_buffer = NULL;
	}
	return (line);
}