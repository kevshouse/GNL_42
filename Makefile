# Define variables
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -D BUFFER_SIZE=42
SRC = get_next_line.c get_next_line_utils.c main.c
OBJ = $(SRC:.c=.o)
NAME = a.out

# Default target
all: $(NAME)

# Rule to create the executable
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target to remove object files
clean:
	rm -f $(OBJ)

# Fclean target to remove executable and object files
fclean: clean
	rm -f $(NAME)

# Recompile the program
re: fclean all
