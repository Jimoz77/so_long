/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fonc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:22:17 by jimpa             #+#    #+#             */
/*   Updated: 2025/02/02 20:08:20 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_visited(t_map *map, bool **visited)
{
	int	i;

	i = 0;
	while (i < map->height)
		free(visited[i++]);
	free(visited);
}

bool	**initialize_visited(t_map *map)
{
	bool	**visited;
	int		i;

	visited = (bool **)malloc(map->height * sizeof(bool *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		visited[i] = (bool *)malloc(map->width * sizeof(bool));
		if (!visited[i])
		{
			while (i-- > 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		ft_memset(visited[i], 0, map->width * sizeof(bool));
		i++;
	}
	return (visited);
}

bool	check_exit(t_map *map, bool **visited, t_map_solv *s)
{
	s->i = 0;
	while (s->i < map->height)
	{
		s->j = 0;
		while (s->j < map->width)
		{
			visited[s->i][s->j] = false;
			if (map->m_dat[s->i][s->j] == 'E')
			{
				s->exit_x = s->j;
				s->exit_y = s->i;
			}
			s->j++;
		}
		s->i++;
	}
	return (s->exit_x != -1 && s->exit_y != -1);
}

bool	is_map_solvable(t_map *map)
{
	t_map_solv	s;
	bool		**visited;

	s.exit_x = -1;
	s.exit_y = -1;
	s.player = find_player(map);
	if (!is_player(map, &s.player.x, &s.player.y))
		return (false);
	visited = initialize_visited(map);
	if (!visited)
		return (false);
	if (!check_exit(map, visited, &s))
	{
		free_visited(map, visited);
		return (false);
	}
	s.result = dfs(map, visited, &s);
	free_visited(map, visited);
	return (s.result);
}

void	reset_visited(t_map *map, bool **visited)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		ft_memset(visited[i], 0, map->width * sizeof(bool));
		i++;
	}
}
