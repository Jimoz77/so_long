/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_fonc2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:13:57 by jiparcer          #+#    #+#             */
/*   Updated: 2025/02/01 17:17:47 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//Trouver la position actuelle du joueur
int	move_player(t_map *map, int keycode, int max_coin)
{
	t_move		cord;

	cord.y = 0;
	while (cord.y < map->height)
	{
		cord.x = 0;
		while (cord.x < map->width)
		{
			if (map->m_dat[cord.y][cord.x] == 'P')
				break ;
			cord.x++;
		}
		if (cord.x < map->width && map->m_dat[cord.y][cord.x] == 'P')
			break ;
		cord.y++;
	}
	if (cord.x >= map->width || cord.y >= map->height)
		return (0);
	cord.n_x = cord.x;
	cord.n_y = cord.y;
	return (move_player2(map, keycode, max_coin, cord));
}

int	key_input(int keycode, t_params *param)
{
	t_point	old;
	t_point	new;
	int		change;

	change = 0;
	if (keycode == 65307)
	{
		free_params(param);
		exit(0);
	}
	old = find_player(param->map);
	change = move_player(param->map, keycode, param->max_coin);
	new = find_player(param->map);
	if (change == 1 && (new.x == 0 && new.y == 0))
		new = find_d(param->map);
	if (change == 1)
	{
		draw_tiles(*param, old, new);
		mlx_put_image_to_window(param->mlx_ptr, param->win_ptr, \
		param->img->img, 0, 0);
	}
	return (0);
}
