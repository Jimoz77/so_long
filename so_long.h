#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include "gnl/get_next_line.h"

typedef struct s_data
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}           t_data;

typedef struct s_map
{
    char    **map_data;
    int     width;
    int     height;
}           t_map;

typedef struct s_sprite
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
}           t_sprite;

#define tile_size 32

#define sprite_floor_x 0
#define sprite_floor_y 0

#define sprite_wall_x 96
#define sprite_wall_y 0

#define sprite_player_x 128
#define sprite_player_y 0

#define sprite_coin_x 160
#define sprite_coin_y 0

#define sprite_exit_x 192
#define sprite_exit_y 0

#endif