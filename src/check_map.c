/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:00:25 by jiparcer          #+#    #+#             */
/*   Updated: 2025/02/01 17:40:29 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_corn2(t_map *map, t_map_corn c)
{
	while (c.y >= 0)
	{
		if (map->m_dat[c.y][c.x] != '1')
			return (0);
		c.y--;
	}
	while (c.x >= 0)
	{
		if (map->m_dat[c.y_max][c.x] != '1')
			return (0);
		c.x--;
	}
	return (1);
}

int	check_map_corners(t_map *map)
{
	t_map_corn	c;

	c.x = 0;
	c.y = 0;
	while (c.x < (map->width - 1))
	{
		if (map->m_dat[0][c.x] != '1')
			return (0);
		c.x++;
	}
	while (c.y < map->height - 1)
	{
		if (map->m_dat[c.y][0] != '1')
			return (0);
		c.y++;
	}
	c.y_max = c.y;
	c.x--;
	return (check_map_corn2(map, c));
}

void	map_checker(t_params *params)
{
	int	result;

	result = 1;
	if (check_carac(params->map) == 0)
	{
		ft_printf("Error\nLA MAP N'EST PAS FERMÈE, INCOMPLÈTE OU INSOLVABLE\n");
		free_params(params);
		exit(0);
	}
	if (line_lenght_checker(params->map) == 0)
		result = 0;
	if (check_map_corners(params->map) == 0)
		result = 0;
	if (is_map_solvable(params->map) == 0 || \
	!are_collectibles_reachable(params->map))
		result = 0;
	if (result == 0)
	{
		ft_printf("Error\nLA MAP N'EST PAS FERMÈE, INCOMPLÈTE OU INSOLVABLE\n");
		free_params(params);
		exit (0);
	}
}

bool	are_collectibles_reachable(t_map *map)
{
	t_collect	c;
	bool		**visited;

	if (!is_player(map, &c.player_x, &c.player_y))
		return (false);
	visited = initialize_visited(map);
	if (!visited)
		return (false);
	if (!check_collectibles(map, visited, &c))
	{
		c.i = 0;
		while (c.i < map->height)
			free(visited[c.i++]);
		free(visited);
		return (false);
	}
	c.i = 0;
	while (c.i < map->height)
		free(visited[c.i++]);
	free(visited);
	return (true);
}

bool	check_collectibles(t_map *map, bool **visited, t_collect *c)
{
	c->i = 0;
	while (c->i < map->height)
	{
		c->j = 0;
		while (c->j < map->width)
		{
			if (map->m_dat[c->i][c->j] == 'C')
			{
				reset_visited(map, visited);
				if (!dfs(map, visited, c->player_x, c->player_y, c->j, c->i))
					return (false);
			}
			c->j++;
		}
		c->i++;
	}
	return (true);
}
