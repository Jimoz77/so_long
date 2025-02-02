/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_fonc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:45:20 by jimpa             #+#    #+#             */
/*   Updated: 2025/02/02 20:29:07 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_valid_move(t_map *map, bool **visited, int x, int y)
{
	return (x >= 0 && y >= 0 && x < map->width && y < map->height && \
	map->m_dat[y][x] != '1' && !visited[y][x]);
}

bool	is_player(t_map *map, int *x, int *y)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->m_dat[i][j] == 'P')
			{
				*x = j;
				*y = i;
				player++;
			}
			j++;
		}
		i++;
	}
	if (player == 1)
		return (true);
	return (false);
}

void	draw_sprite_p(t_params p, int start_x, int start_y)
{
	t_sprite_params	sp;

	sp.sprite_x = SPRITE_PLAYER_X;
	sp.sprite_y = SPRITE_PLAYER_Y;
	draw_sprite(p, start_x, start_y, sp);
}

void	draw_sprite_0(t_params p, int start_x, int start_y)
{
	t_sprite_params	sp;

	sp.sprite_x = SPRITE_FLOOR_X;
	sp.sprite_y = SPRITE_FLOOR_Y;
	draw_sprite(p, start_x, start_y, sp);
}

void	draw_sprite_1(t_params p, int start_x, int start_y)
{
	t_sprite_params	sp;

	sp.sprite_x = SPRITE_WALL_X;
	sp.sprite_y = SPRITE_WALL_Y;
	draw_sprite(p, start_x, start_y, sp);
}
