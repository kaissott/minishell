CFLAGS = -Wall -Wextra -Werror -g3

NAME = libft.a

BONUS = ft_lstnew_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstmap_bonus.c \

OBJBONUS = $(BONUS:.c=.o)

SRC = ft_atoi.c \
	ft_bzero.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_memcmp.c \
	ft_strchr.c \
	ft_strstr.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strrchr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_strnstr.c \
	ft_strdup.c \
	ft_calloc.c \
	ft_strnstr.c \
	ft_substr.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strjoin.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_strcmp.c \
	ft_lstadd_back_bonus.c \
	handle_error_exit.c \
	handle_error.c \
	ft_atoll.c \
	ft_isspace.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	split_charset.c

OBJ = $(SRC:.c=.o)

%.o : %.c libft.h
	cc $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)

bonus : $(OBJBONUS)
	ar rc $(NAME) $(OBJBONUS)

clean:
	rm -f $(OBJ) $(OBJBONUS)

fclean: clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re bonus
