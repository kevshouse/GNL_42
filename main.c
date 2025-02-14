/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keanders <keanders@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:21:26 by keanders          #+#    #+#             */
/*   Updated: 2025/01/28 14:21:41 by keanders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
// Compile with:
// gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c 
//      get_next_line_utils.c

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0) // Added error handling for file opening
    {
        perror("Error opening file");
        return (1);
    }
    
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
