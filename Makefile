# Exit
NAME = pipex

# Compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra

LIBFT_DIR = libft/

# Sources
SRC = main.c pipex.c

OBJS =	$(SRC:.c=.o)

# Linking
INCLUDE = -L ./libft -lft

$(NAME):$(OBJS)
	make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDE)

# Recompile object files if pipex.h changes  
$(OBJS): pipex.h

# Default target for compilation
all: $(NAME)

# Clean objects
clean:
	rm -f $(OBJS)
	cd $(LIBFT_DIR) && $(MAKE) clean

# Clean objects and executable
fclean: clean
	rm -f $(NAME)
	cd $(LIBFT_DIR) && $(MAKE) fclean

# Clean objects and executable and then compilation but just OBJS
re: fclean all

# Key words
.PHONY: all clean fclean re