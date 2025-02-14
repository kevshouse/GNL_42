#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
ssize_t	read_from_fd(int fd, char *tmp_buf);
char	*update_buffer(char **buf, char *tmp_buf, ssize_t bytes_read);

#endif
