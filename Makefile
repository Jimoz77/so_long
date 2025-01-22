# Nom du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -Werror -I/usr/local/include/ -I./gnl

# Dossier où se trouvent les fichiers objets
OBJ_DIR = obj

# Nom de l'exécutable
NAME = so_long

# Liste des fichiers sources
SRCS = test3_prob_size.c gnl/get_next_line.c gnl/get_next_line_utils.c ft_printf/libftprintf.a ft_printf/libft/libft.a

# Génère les fichiers objets correspondants
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Lien des bibliothèques
LDFLAGS = -L/usr/local/lib -Lminilibx-linux -lmlx_Linux -lX11 -lXext

# Commande de génération des fichiers objets
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Commande de compilation de l'exécutable
$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

# Cible pour nettoyer les fichiers objets
clean:
	rm -rf $(OBJ_DIR)

# Cible pour nettoyer les fichiers objets et l'exécutable
fclean: clean
	rm -f $(NAME)

# Cible pour recompiler le projet entièrement
re: fclean $(NAME)

# Cible par défaut
.PHONY: all clean fclean re
all: $(NAME)








#For object files, you could add the following rule to your makefile, assuming that you have the mlx for linux source in a directory named mlx_linux in the root of your project:

#%.o: %.c
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@


#To link with the required internal Linux API:

#$(NAME): $(OBJ)
#	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

