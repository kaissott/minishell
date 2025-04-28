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

LST_UTILS :=	utils.c

LST_INC :=	minishell.h structures.h

#Directories
D_SRC :=	src/
D_INC :=	includes/

D_UTILS :=	utils/

D_OBJ :=	.obj/

#Files full path
SRC :=	$(addprefix $(D_SRC), $(LST_EXEC)) \
		$(addprefix $(D_SRC)$(D_UTILS), $(LST_UTILS))

INC :=	$(addprefix $(D_INC), $(LST_INC))

OBJ :=	$(subst $(D_SRC), $(D_OBJ), $(SRC:.c=.o))

#Libraries
D_LIBFT :=	libft/
LIBFT := $(D_LIBFT)libft.a

#################################################################################
################				BASIC VARIABLES					#################
#################################################################################

CC := cc
CFLAGS := -Wall -Wextra
IFLAGS := -I$(D_INC)

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
