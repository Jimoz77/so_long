SRCS = ft_printf.c fonction_format.c fonction_format2.c libft/libft.a
OBJECTS = ${SRCS:.c=.o}
HEADERS = ft_printf.h
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
NAME = libftprintf.a
LIBC = ar rcs
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	cd $(LIBFT_PATH) && make

$(NAME): $(LIBFT) $(OBJECTS)
	$(LIBC) $(NAME) $(OBJECTS) $(LIBFT)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_PATH) clean
	rm -f $(OBJECTS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
