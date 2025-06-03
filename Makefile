# Couleurs
GREEN  = \033[1;32m
CYAN   = \033[1;36m
RED    = \033[1;31m
ORANGE = \033[38;5;208m
RESET  = \033[0m

# Nom de l'exécutable
NAME = minishell

# Dossiers
DIR_LIBFT = Libft/
DIR_OBJ = obj/
DIR_INC = include/

# Sources
SRC = \
	builtins/mini_cd.c \
	builtins/mini_echo.c \
	builtins/mini_env_free.c \
	builtins/mini_env.c \
	builtins/mini_exit.c \
	builtins/mini_exit_free.c \
	builtins/mini_pwd.c \
	builtins/main.c \
	builtins/create_node.c \
	builtins/mini_export.c \
	builtins/mini_unset.c \
	builtins/free_structs.c \
	exec_single_cmd/exec_simple_cmd.c \
	exec_single_cmd/exec_single_error_handling/error_free.c \
	exec_single_cmd/exec_single_error_handling/single_cmd_error.c \
	exec_single_cmd/ft_split_slash.c \
	env/env_lst.c \
	env/env_to_tab.c \
	env/lst_add.c \
	exec_pipe/exec_pipe.c \
	exec_pipe/exec_pipe_utils.c \
	exec_pipe/exec_pipe_error.c \
	exec_pipe/strrchr_slash.c

# Objets avec dossier obj/ et la hiérarchie complète
OBJ = $(patsubst %.c, $(DIR_OBJ)%.o, $(SRC))

# Includes
INC = $(wildcard $(DIR_INC)/*.h)

# Librairie
LIBFT = $(DIR_LIBFT)libft.a

# Commandes
RM = rm -rf
CC = cc
CFLAGS =-I$(DIR_INC) -I$(DIR_LIBFT) -g

# Build principal
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "\n$(ORANGE)🔗 Linking...$(RESET)"
	@$(CC) $(OBJ) -lreadline $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✅ Build terminé : $(NAME) créé.$(RESET)"

# Compilation : transforme src/*.c → obj/*.o (en conservant sous-dossiers)
$(DIR_OBJ)%.o: %.c $(INC)
	@mkdir -p $(dir $@)
	@echo "$(CYAN)🛠️  Compilation : $< → $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Librairie libft
$(LIBFT):
	@echo "\n$(CYAN)📚 Compilation de libft...$(RESET)"
	@$(MAKE) -C $(DIR_LIBFT)

# Nettoyage des .o et libft
clean:
	@echo "$(ORANGE)🧹 Nettoyage des fichiers objets...$(RESET)"
	@$(RM) $(DIR_OBJ)
	@$(MAKE) -C $(DIR_LIBFT) clean

fclean: clean
	@echo "$(RED)❌ Suppression de l'exécutable $(NAME)...$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
