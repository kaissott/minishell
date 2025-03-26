.PHONY: all clean fclean re bonus makelibft

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

CC = cc



SRC				=	ft_adress.c					ft_baseten.c 				\
					ft_char.c					ft_printf.c					\
					ft_putnbrs.c				ft_itoa.c					\
					ft_strlen.c

OBJ 			=	$(SRC:.c=.o)



all : $(NAME)

%.o : %.c ft_printf.h Makefile
	cc $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ) -o $@

clean:
	rm -f $(OBJ)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re : fclean all
