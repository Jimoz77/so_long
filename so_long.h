/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:34:45 by jimpa             #+#    #+#             */
/*   Updated: 2025/01/20 18:46:13 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include "gnl/get_next_line.h"
# include "ft_printf/ft_printf.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_map
{
	char	**map_data;
	int		width;
	int		height;
}			t_map;

typedef struct s_sprite
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_sprite;

typedef struct s_params {
    t_data *img;
    t_map *map;
    t_sprite *sprite;
    void *mlx_ptr;
    void *win_ptr;
    int zoom;
} t_params;

typedef struct
{
	int x;
	int y;
}	point;



# define TILE_SIZE 32

# define SPRITE_FLOOR_X 0
# define SPRITE_FLOOR_Y 0

# define SPRITE_WALL_X 96
# define SPRITE_WALL_Y 0

# define SPRITE_PLAYER_X 128
# define SPRITE_PLAYER_Y 0

# define SPRITE_COIN_X 160
# define SPRITE_COIN_Y 0

# define SPRITE_EXIT_DONE_X 192
# define SPRITE_EXIT_DONE_Y 0

# define SPRITE_EXIT_X 224
# define SPRITE_EXIT_Y 0

#endif