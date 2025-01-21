FILE	=	ft_strlen.c ft_tolower.c ft_itoa.c ft_putchar.c\
			ft_putstr.c ft_itoa_base.c ft_unitoa.c ft_itoa_base_printf.c

OBJS	=	$(FILE:.c=.o)

CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror -I.
LIBC	=	ar rcs
NAME	=	libft.a

all:		$(NAME)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	${OBJS}
			${LIBC} ${NAME} ${OBJS}
clean:		
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
