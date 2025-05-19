
NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra
RM			= rm -f

# Dossiers
SRC_DIR		= builtins
LIBFT_DIR	= libft
INCLUDES	= -I./ -Iinclude -I$(LIBFT_DIR)

# Fichiers sources
SRC			= $(wildcard $(SRC_DIR)/*.c) \
				main.c

OBJ			= $(SRC:.c=.o)
LIBFT_A		= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT_A) -lreadline -lncurses -o $(NAME)

clean:
	$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

	.PHONY: all clean fclean re
