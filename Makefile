# Exit
NAME = pipex
NAME_BONUS = pipex_bonus

# Compilation
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I gnl/

LIBFT_DIR = libft/

# Sources
SRC = main.c pipex.c

OBJS =	$(SRC:.c=.o)

BONUS = bonus/main_bonus.c bonus/pipex_bonus.c bonus/utils_bonus.c \
		gnl/get_next_line.c gnl/get_next_line_utils.c

BONUS_OBJS = $(BONUS:.c=.o)

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
	rm -f $(OBJS) $(BONUS_OBJS)
	make -C $(LIBFT_DIR) clean

# Clean objects and executable
fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	cd $(LIBFT_DIR) && $(MAKE) fclean

# Clean objects and executable and then compilation but just OBJS
re: fclean all

# Bonus
bonus: $(BONUS_OBJS)
	make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAME_BONUS) $(INCLUDE)

rebonus: fclean bonus

# Recompile bonus object files if pipex_bonus.h changes  
$(BONUS_OBJS): bonus/pipex_bonus.h

# Key words
.PHONY: all clean fclean re bonus rebonus