.PHONY: all clean fclean re bonus
NAME			= libft.a

#################################################################################
################					MAKEFILE TREE				#################
#################################################################################

CC				= cc
CFLAGS			= -Wall -Wextra -Werror -g3
INC				= libft.h

SRCS			=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c \
					ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
					ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
					ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
					ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
					ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
					ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
					ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
					ft_tolower.c ft_toupper.c

OBJS			= $(SRCS:.c=.o)

BONUS			=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
					ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
					ft_lstmap_bonus.c

BONUS_OBJS		= $(BONUS:.c=.o) $(OBJS)

# Étape 1 : Compilation complète
all:			$(NAME)

# Étape 1.5 : Compilation avec bonus
bonus:			$(BONUS_OBJS)
				@echo "\n📚 Creating $(NAME)..."
				@ar rcs $(NAME) $(BONUS_OBJS)
				@echo "✅ $(NAME) compiled successfully.\n"

# Étape 2 & 3 : Compilation + Assemblage (Génération des .o)
%.o :			%.c $(INC)
				@echo "🛠️ Compiling $<"
				@$(CC) $(CFLAGS) -o $@ -c $<

# Étape 4 : Archivage (Création de la bibliothèque)
$(NAME):		$(OBJS)
				@echo "\n📚 Creating $(NAME)..."
				@ar rcs $(NAME) $(OBJS)
				@echo "✅ $(NAME) created successfully.\n"

# Étape 5 : Nettoyage des fichiers objets
clean:
				@echo "\n🧹 Cleaning $(NAME) object files..."
				@rm -f $(OBJS)
				@echo "✅ Object files removed.\n"

# Étape 6 : Nettoyage complet (libft.a)
fclean:			clean
				@echo "🧹 Cleaning $(NAME)..."
				@rm -f $(NAME)
				@echo "✅ Full $(NAME) cleanup done.\n"

# Étape 7 : Recompilation complète
re:				fclean $(NAME)
