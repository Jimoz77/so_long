/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_fonc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:56:05 by jimpa             #+#    #+#             */
/*   Updated: 2025/01/31 15:42:33 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	find_d(t_map *map)
{
	t_point	player;

	player.y = 0;
	while (player.y < map->height)
	{
		player.x = 0;
		while (player.x < map->width)
		{
			if (map->m_dat[player.y][player.x] == 'D')
				return (player);
			player.x++;
		}
		player.y++;
	}
	player.x = 0;
	player.y = 0;
	return (player);
}

t_point	find_player(t_map *map)
{
	t_point	player;

	player.y = 0;
	while (player.y < map->height)
	{
		player.x = 0;
		while (player.x < map->width)
		{
			if (map->m_dat[player.y][player.x] == 'P')
				return (player);
			player.x++;
		}
		player.y++;
	}
	player.x = 0;
	player.y = 0;
	return (player);
}

void	print_move(void)
{
	static int	move = 1;

	ft_printf("mouvements : %d\n", move);
	move++;
}

int	move_player3(t_map *m, int kcode, int max_coin, t_move cd)
{
	static int	coin_w = 0;

	if (cd.n_x >= 0 && cd.n_x < m->width && cd.n_y >= 0 && cd.n_y < m->height \
	&& (kcode == 100 || kcode == 97 || kcode == 115 || kcode == 119))
	{
		if (m->m_dat[cd.n_y][cd.n_x] != '1' && m->m_dat[cd.n_y][cd.n_x] != 'E')
		{
			if (m->m_dat[cd.n_y][cd.n_x] == 'C')
				coin_w++;
			m->m_dat[cd.y][cd.x] = '0';
			m->m_dat[cd.n_y][cd.n_x] = 'P';
			print_move();
			return (1);
		}
		else if (m->m_dat[cd.n_y][cd.n_x] == 'E' && coin_w == max_coin)
		{
			m->m_dat[cd.y][cd.x] = '0';
			m->m_dat[cd.n_y][cd.n_x] = 'D';
			print_move();
			return (1);
		}
	}
	return (0);
}

int	move_player2(t_map *map, int keycode, int max_coin, t_move cord)
{
	if (keycode == 119)
		cord.n_y--;
	else if (keycode == 115)
		cord.n_y++;
	else if (keycode == 97)
		cord.n_x--;
	else if (keycode == 100)
		cord.n_x++;
	return (move_player3(map, keycode, max_coin, cord));
}

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

int	key_input(int keycode, t_params param)
{
	t_point	old;
	t_point	new;
	int		change;

	change = 0;
	if (keycode == 65307)
	{
		free_params(&param);
		exit(0);
	}
	old = find_player(param.map);
	change = move_player(param.map, keycode, param.max_coin);
	new = find_player(param.map);
	if (change == 1 && (new.x == 0 && new.y == 0))
		new = find_d(param.map);
	if (change == 1)
	{
		draw_tiles(param, old, new);
		mlx_put_image_to_window(param.mlx_ptr, param.win_ptr, \
		param.img->img, 0, 0);
	}
	return (0);
}
