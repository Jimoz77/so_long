# Nom du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -Werror -g

# Dossier où se trouvent les fichiers objets
OBJ_DIR = obj

# Nom de l'exécutable
NAME = so_long

# Liste des fichiers sources
SRCS = src/main.c src/exit_fonc.c src/map_fonc.c src/draw_tile.c src/move_fonc.c src/sprite_fonc.c src/sprite_fonc2.c src/else.c gnl/get_next_line.c gnl/get_next_line_utils.c

# Génère les fichiers objets correspondants
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Lien des bibliothèques
MLX_PATH = ./minilibx-linux
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lX11 -lXext -lXrender -lXrandr -lXcursor -lm -lpthread
INC_FLAGS = -Iincludes -Imlx -I/usr/include -I$(MLX_PATH)

# Variables pour les fichiers .a
SRCPTF = ft_printf/libftprintf.a
SRCLIBFT = ft_printf/libft/libft.a

# Commande de génération des fichiers objets
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# Commande de compilation de l'exécutable
$(NAME): $(OBJS) $(SRCPTF) $(MLX_PATH)/libmlx_linux.a
	$(CC) $(CFLAGS) $(OBJS) $(SRCPTF) $(SRCLIBFT) -o $(NAME) $(MLX_FLAGS)

# Cible pour compiler libftprintf.a
$(SRCPTF):
	$(MAKE) -C ft_printf

# Cible pour compiler minilibx
$(MLX_PATH)/libmlx_linux.a:
	$(MAKE) -C $(MLX_PATH)

# Cible pour nettoyer les fichiers objets
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C ft_printf clean
	$(MAKE) -C ft_printf/libft clean
	$(MAKE) -C $(MLX_PATH) clean

# Cible pour nettoyer les fichiers objets et l'exécutable
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ft_printf fclean
	$(MAKE) -C ft_printf/libft fclean
	$(MAKE) -C $(MLX_PATH) clean

# Cible pour recompiler le projet entièrement
re: fclean $(NAME)

# Cible par défaut
.PHONY: all clean fclean re
all: $(NAME)