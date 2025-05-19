GREEN  = \033[1;32m
CYAN   = \033[1;36m
RED    = \033[1;31m
ORANGE = \033[38;5;208m
RESET  = \033[0m

NAME = pipex
NAME_BONUS = pipex_bonus

DIR_LIBFT = Libft/
DIR_BONUS = bonus/
DIR_OBJ = obj/
DIR_OBJ_BONUS = obj/
DIR_SRC = mandatory/
DIR_INC = include/

LST_EXEC = error.c ft_split_slash.c main.c pipex_utils.c strrchr_slash.c open.c
LST_BONUS = main_bonus.c error_bonus.c ft_split_slash_bonus.c pipex_utils_bonus.c \
			strrchr_slash_bonus.c open_bonus.c
LST_INC = pipex.h
LST_INC_BONUS = pipex_bonus.h

SRC = $(addprefix $(DIR_SRC), $(LST_EXEC))
BONUS = $(addprefix $(DIR_BONUS), $(LST_BONUS))
INC = $(addprefix $(DIR_INC), $(LST_INC))
INC_BONUS = $(addprefix $(DIR_INC), $(LST_INC_BONUS))
OBJ = $(subst $(DIR_SRC), $(DIR_OBJ), $(SRC:.c=.o))
OBJBONUS = $(subst $(DIR_BONUS), $(DIR_OBJ_BONUS), $(BONUS:.c=.o))
LIBFT = $(DIR_LIBFT)libft.a

RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror
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
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\n$(GREEN)🎉 Mandatory build successful!$(RESET)\n"

$(NAME_BONUS): $(OBJBONUS) $(LIBFT)
	@echo "\n$(ORANGE)🔗 Linking objects to create $(NAME_BONUS)...$(RESET)\n"
	@$(CC) $(OBJBONUS) $(LIBFT) -o $(NAME_BONUS)
	@echo "\n$(GREEN)🎉 Bonus build successful!$(RESET)\n"

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(INC) Makefile | $(DIR_OBJ)
	@echo "$(CYAN)🛠️  Compilation de $< $(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(DIR_OBJ_BONUS)%.o: $(DIR_BONUS)%.c $(INC_BONUS) Makefile | $(DIR_OBJ_BONUS)
	@echo "$(CYAN)🛠️  Compilation de $< $(RESET)"
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

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
	@echo "$(RED)❌ Removing executables $(NAME) and $(NAME_BONUS)...\n\033[0m"
	@${RM} $(NAME) $(NAME_BONUS)
	@$(MAKECMD) fclean -C $(DIR_LIBFT) > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re bonus
