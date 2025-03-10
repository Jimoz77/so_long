/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:34:45 by jimpa             #+#    #+#             */
/*   Updated: 2025/02/02 20:09:24 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include "../gnl/get_next_line.h"
# include "../ft_printf/ft_printf.h"
# include "../minilibx-linux/mlx_int.h"

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
	char	**m_dat;
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

typedef struct s_params
{
	t_data		*img;
	t_map		*map;
	t_sprite	*sprite;
	void		*mlx_ptr;
	void		*win_ptr;
	int			zoom;
	int			max_coin;
}	t_params;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_move
{
	int	x;
	int	y;
	int	n_x;
	int	n_y;
}	t_move;

typedef struct s_draw
{
	char	*pixel;
	int		color;
	int		dx;
	int		dy;
	int		x;
	int		y;
	int		start_x;
	int		start_y;
	int		sprite_x;
	int		sprite_y;
}	t_draw;

typedef struct s_sprite_params
{
	int	sprite_x;
	int	sprite_y;
}	t_sprite_params;

typedef struct s_draw_params
{
	t_draw	draw;
	int		start_x;
	int		start_y;
}	t_draw_params;

typedef struct s_collect
{
	int		player_x;
	int		player_y;
	int		j;
	int		i;
	int		k;
	int		l;
}	t_collect;

typedef struct s_map_solv
{
	t_point	player;
	bool	result;
	int		exit_x;
	int		exit_y;
	int		i;
	int		j;
}	t_map_solv;

typedef struct s_map_corn
{
	int	x;
	int	y;
	int	y_max;
}	t_map_corn;

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

# define ZOOM_FACTOR 3

int			coin_counter(t_map *map);
int			line_lenght_checker(t_map *map);
int			check_carac(t_map *map);
void		free_params(t_params *params);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
bool		is_valid_move(t_map *map, bool **visited, int x, int y);
bool		dfs(t_map *map, bool **visited, t_map_solv *s);
void		error_case(t_params *params, int c);
t_point		find_player(t_map *map);
bool		is_player(t_map *map, int *x, int *y);
bool		is_map_solvable(t_map *map);
int			check_map_corners(t_map *map);
void		draw_sprite(t_params p, int start_x, int start_y, \
			t_sprite_params sp);
void		draw_sprite_1(t_params p, int start_x, int start_y);
void		draw_sprite_0(t_params p, int start_x, int start_y);
void		draw_sprite_p(t_params p, int start_x, int start_y);
void		draw_sprite_c(t_params p, int start_x, int start_y);
void		draw_sprite_e(t_params p, int start_x, int start_y);
void		draw_sprite_d(t_params p, int start_x, int start_y);
void		draw_map(t_params p);
bool		are_collectibles_reachable(t_map *map);
void		draw_tiles(t_params p, t_point old, t_point new);
int			move_player(t_map *map, int keycode, int max_coin);
int			key_input(int keycode, t_params *param);
int			close_win_cross(t_params *param);
t_sprite	*load_sprite(void *mlx, char *file_path);
t_map		*read_map(char *file_name);
void		free_visited(t_map *map, bool **visited);
bool		**initialize_visited(t_map *map);
bool		check_exit(t_map *map, bool **visited, t_map_solv *s);
bool		is_map_solvable(t_map *map);
void		reset_visited(t_map *map, bool **visited);
bool		check_collectibles(t_map *map, bool **visited, t_map_solv *c);
bool		are_collectibles_reachable(t_map *map);
void		map_checker(t_params *params);
t_point		find_d(t_map *map);
void		print_move(void);
int			move_player3(t_map *m, int kcode, int max_coin, t_move cd);
int			move_player2(t_map *map, int keycode, int max_coin, t_move cord);

#endif