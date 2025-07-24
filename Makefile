#################################################################################
################					MAKEFILE					#################
#################################################################################

.PHONY:	all clean fclean re deps bonus show_compiling_msg
NAME :=	minishell

#################################################################################
################					FILE TREE					#################
#################################################################################

#Files
LST_EXEC :=	minishell.c init_minishell.c close_error_handler.c utils.c

LST_BUILTINS :=	mini_cd.c mini_echo.c \
				mini_env.c mini_exit_free.c mini_exit.c mini_export.c \
				mini_pwd.c mini_unset.c mini_cd_utils.c mini_export_utils.c \

LST_ENV :=		env_lst.c env_to_tab.c lst_add.c

LST_EXEC_PIPE :=	exec_pipe_error.c exec_pipe_utils.c exec_pipe.c exec_pipe_start.c exec_error1.c sig.c

LST_EXEC_SINGLE_CMD :=	error_free.c exec_simple_cmd.c  single_cmd_error.c exec_global_utils.c

LST_EXEC_UTILS := exec_dup.c strrchr_slash.c ft_split_slash.c init_exec.c free_structs.c\
				free_structs2.c

LST_PARSING :=	expansion_utils.c expansion.c parse_utils.c parse.c \
				tokenisation_utils.c tokenisation.c word_splitting_utils.c word_splitting.c

LST_UTILS :=	file_utils.c utils.c

LST_DEBUG_UTILS :=	print_lst_utils.c

LST_LST_UTILS :=	chunk_lst_utils.c exec_lst_utils.c \
					expand_lst_utils.c token_lst_utils.c word_splitting_token_lst_utils.c

LST_LST_FREE_UTILS :=	exec_free_utils.c expand_free_utils.c token_free_utils.c

LST_INC :=	minishell.h structures.h utils.h

LST_INC_PARSING :=	expansion.h parse.h tokenisation.h word_splitting.h

LST_INC_PARSING_UTILS :=	debug_utils.h lst_utils.h parse_utils.h

LST_INC_EXEC :=	builtins.h error.h main.h

#Directories
D_SRC :=	src/
D_INC :=	includes/

D_EXEC :=	exec/

D_BUILTINS :=	builtins/

D_ENV :=	env/

D_EXEC_PIPE :=	exec_pipe/

D_EXEC_SINGLE_CMD :=	exec_single_cmd/

D_EXEC_UTILS :=	exec_utils/

D_PARSING :=	parsing/

D_UTILS :=	utils/

D_DEBUG_UTILS :=	debug_utils/

D_LST_UTILS :=	lst_utils/

D_LST_FREE_UTILS :=	lst_free_utils/

D_INC_EXEC :=	exec/

D_INC_PARSING :=	parsing/

D_INC_UTILS :=	utils/

D_OBJ :=	.obj/

#Files full path
SRC :=	$(addprefix $(D_SRC), $(LST_EXEC)) \
		$(addprefix $(D_SRC)$(D_EXEC)$(D_BUILTINS), $(LST_BUILTINS)) \
		$(addprefix $(D_SRC)$(D_EXEC)$(D_ENV), $(LST_ENV)) \
		$(addprefix $(D_SRC)$(D_EXEC)$(D_EXEC_PIPE), $(LST_EXEC_PIPE)) \
		$(addprefix $(D_SRC)$(D_EXEC)$(D_EXEC_SINGLE_CMD), $(LST_EXEC_SINGLE_CMD)) \
		$(addprefix $(D_SRC)$(D_EXEC)$(D_EXEC_UTILS), $(LST_EXEC_UTILS)) \
		$(addprefix $(D_SRC)$(D_PARSING), $(LST_PARSING)) \
		$(addprefix $(D_SRC)$(D_PARSING)$(D_UTILS), $(LST_UTILS)) \
		$(addprefix $(D_SRC)$(D_PARSING)$(D_UTILS)$(D_DEBUG_UTILS), $(LST_DEBUG_UTILS)) \
		$(addprefix $(D_SRC)$(D_PARSING)$(D_UTILS)$(D_LST_UTILS), $(LST_LST_UTILS)) \
		$(addprefix $(D_SRC)$(D_PARSING)$(D_UTILS)$(D_LST_UTILS)$(D_LST_FREE_UTILS), $(LST_LST_FREE_UTILS))

INC :=	$(addprefix $(D_INC), $(LST_INC)) \
		$(addprefix $(D_INC)$(D_INC_EXEC), $(LST_INC_EXEC)) \
		$(addprefix $(D_INC)$(D_INC_PARSING), $(LST_INC_PARSING)) \
		$(addprefix $(D_INC)$(D_INC_PARSING)$(D_INC_UTILS), $(LST_INC_PARSING_UTILS))

OBJ :=	$(subst $(D_SRC), $(D_OBJ), $(SRC:.c=.o))

#Libraries
D_LIBFT :=	libft/
LIBFT := $(D_LIBFT)libft.a

#################################################################################
################				BASIC VARIABLES					#################
#################################################################################

CC := cc
CFLAGS := -Wall -Wextra -g3 -g
IFLAGS := -I$(D_INC) -I$(D_INC)$(D_INC_PARSING) -I$(D_INC)$(D_INC_UTILS) -I/opt/homebrew/opt/readline/include
LDFLAGS := -L/opt/homebrew/opt/readline/lib -lreadline -lpthread

RM := rm -rf
MAKE_CMD := @$(MAKE) --no-print-directory

#################################################################################
################					RULES						#################
#################################################################################

# Step 1 : Full compilation
all:
	@echo "\n🚀 Building $(NAME) :"
	$(MAKE_CMD) deps show_compiling_msg $(NAME)

# Step 4 : Links edition (Linking)
$(NAME): $(OBJ) $(LIBFT)
	@echo "✅ Compilation done.\n\n🔗 Linking $(NAME)..."
	@$(CC) $(OBJ) $(LDFLAGS) $(LIBFT) -o $@
	@echo "✅ Linking done.\n\n🎉 ./$(NAME) ready to run!\n"

# Step 2 & 3 : Compilation + Assembly (Generate all .o)
$(D_OBJ)%.o: $(D_SRC)%.c $(INC) Makefile | $(D_OBJ)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(D_OBJ):
	@mkdir -p $(dir $(OBJ))

# Step 1.5 : Compilation of libft
deps:
	@echo "\n🏗️  Building dependencies...\n\n📚 Building libft..."
	$(MAKE_CMD) -C $(D_LIBFT) > /dev/null 2>&1
	@echo "✅ Libft build done.\n\n"

# Step 5 : Cleaning object files
clean:
	@echo "\n🧹 Cleaning $(NAME) object files..."
	@$(RM) $(D_OBJ)
	@echo "✅ Object files removed.\n"

# Step 6 : Full clean (libft + mlx + executable)
fclean: clean
	@echo "🧹 $(NAME)..."
	$(MAKE_CMD) fclean -C $(D_LIBFT) > /dev/null 2>&1
	@$(RM) $(NAME)
	@echo "✨ All clean!\n"

# Step 7 : Full recompilation
re: fclean all

show_compiling_msg:
	@echo "🛠️  Compiling $(NAME)..."
