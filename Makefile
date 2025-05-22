GREEN  = \033[1;32m
CYAN   = \033[1;36m
RED    = \033[1;31m
ORANGE = \033[38;5;208m
RESET  = \033[0m

NAME = minishell

DIR_LIBFT = Libft/
DIR_OBJ = obj/
DIR_INC = include/

LST_EXEC = builtins/lst_add.c builtins/mini_cd.c builtins/mini_echo.c builtins/mini_env_free.c builtins/mini_env.c builtins/mini_exit.c builtins/mini_exit_free.c builtins/mini_pwd.c builtins/main.c exec_single_cmd/exec_simple_cmd.c exec_single_cmd/exec_single_error_handling/error_free.c exec_single_cmd/exec_single_error_handling/single_cmd_error.c exec_single_cmd/ft_split_slash.c
LST_INC = builtins.h error.h main.h struct.h

SRC = $(LST_EXEC)
INC = $(addprefix $(DIR_INC), $(LST_INC))
OBJ = $(SRC:.c=.o)
LIBFT = $(DIR_LIBFT)libft.a

RM = rm -f
CC = cc
MAKECMD = @$(MAKE) --no-print-directory
IFLAGS = -I$(DIR_INC) -I$(DIR_LIBFT)

all:
	@echo "\n$(GREEN)=========================================$(RESET)"
	@echo "$(GREEN)         Démarrage du build            $(RESET)"
	@echo "$(GREEN)=========================================$(RESET)"
	@$(MAKECMD) deps $(NAME)

bonus:
	@echo "\n$(GREEN)=========================================$(RESET)"
	@echo "$(GREEN)         Démarrage du build            $(RESET)"
	@echo "$(GREEN)=========================================$(RESET)"
	@$(MAKECMD) deps $(NAME_BONUS)

$(NAME): $(OBJ) $(LIBFT)
	@echo "\n$(ORANGE)🔗 Linking objects to create $(NAME)...$(RESET)\n"
	@$(CC) $(OBJ) -lreadline $(LIBFT) -o $(NAME)
	@echo "\n$(GREEN)🎉 Mandatory build successful!$(RESET)\n"


$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(INC) Makefile | $(DIR_OBJ)
	@echo "$(CYAN)🛠️  Compilation de $< $(RESET)"
	@$(CC) $(IFLAGS) -c $< -o $@


$(DIR_OBJ):
	@echo "$(CYAN)🗄️ Creating directory $(DIR_OBJ)...\n\033[0m"
	@mkdir -p $@

deps:
	@echo "\n$(CYAN)🛠️ Building dependencies in $(DIR_LIBFT)...\n\033[0m"
	$(MAKECMD) -C $(DIR_LIBFT) > /dev/null 2>&1

clean:
	@echo "\n$(ORANGE)🧹 Cleaning object files...\n\033[0m"
	@rm -rf $(DIR_OBJ)
	@$(MAKECMD) clean -C $(DIR_LIBFT) > /dev/null 2>&1

fclean: clean
	@echo "$(RED)❌ Removing executables $(NAME)...\n\033[0m"
	@${RM} $(NAME)
	@$(MAKECMD) fclean -C $(DIR_LIBFT) > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re bonus
