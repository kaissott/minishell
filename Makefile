#################################################################################
################					MAKEFILE					#################
#################################################################################

.PHONY:	all clean fclean re deps bonus show_compiling_msg
NAME :=	minishell

#################################################################################
################					FILE TREE					#################
#################################################################################

#Files
LST_EXEC :=	minishell.c

LST_PARSING :=	expand_utils.c expand_chunk.c parse_utils.c parse.c \
				tokenisation_utils.c tokenisation.c

LST_UTILS :=	env_utils.c file_utils.c free_utils.c utils.c

LST_LST_UTILS :=	exec_lst_utils.c token_lst_add_utils.c token_lst_utils.c

LST_INC :=	minishell.h structures.h

LST_INC_PARSING :=	expand_chunk.h parse.h tokenisation.h

LST_INC_UTILS :=	lst_utils.h utils.h

#Directories
D_SRC :=	src/
D_INC :=	includes/

D_PARSING :=	parsing/

D_UTILS :=	utils/

D_LST_UTILS :=	lst_utils/

D_INC_PARSING :=	parsing/

D_INC_UTILS :=	utils/

D_OBJ :=	.obj/

#Files full path
SRC :=	$(addprefix $(D_SRC), $(LST_EXEC)) \
		$(addprefix $(D_SRC)$(D_PARSING), $(LST_PARSING)) \
		$(addprefix $(D_SRC)$(D_UTILS), $(LST_UTILS)) \
		$(addprefix $(D_SRC)$(D_UTILS)$(D_LST_UTILS), $(LST_LST_UTILS))

INC :=	$(addprefix $(D_INC), $(LST_INC)) \
		$(addprefix $(D_INC)$(D_INC_PARSING), $(LST_INC_PARSING)) \
		$(addprefix $(D_INC)$(D_INC_UTILS), $(LST_INC_UTILS))

OBJ :=	$(subst $(D_SRC), $(D_OBJ), $(SRC:.c=.o))

#Libraries
D_LIBFT :=	libft/
LIBFT := $(D_LIBFT)libft.a

#################################################################################
################				BASIC VARIABLES					#################
#################################################################################

CC := cc
CFLAGS := -Wall -Wextra -g3
IFLAGS := -I$(D_INC) -I$(D_INC)$(D_INC_PARSING) -I$(D_INC)$(D_INC_UTILS)

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
	@$(CC) $(OBJ) $(LIBFT) -lreadline -lpthread -o $@
	@echo "✅ Linking done.\n\n🎉 ./$(NAME) ready to run!\n"

# Step 2 & 3 : Compilation + Assembly (Generate all .o)
$(D_OBJ)%.o: $(D_SRC)%.c $(INC) Makefile | $(D_OBJ)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(D_OBJ):
	@mkdir -p $(dir $(OBJ))

# Step 1.5 : Compilation of libft and mlx
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
