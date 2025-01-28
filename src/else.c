/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:11:12 by jimpa             #+#    #+#             */
/*   Updated: 2025/01/27 18:11:47 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	coin_counter(t_map *map)
{
	int	i;
	int	j;
	int	coin;

	i = 0;
	coin = 0;
	while (i < map->height - 1)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->m_dat[i][j] == 'C')
				coin++;
			j++;
		}
		i++;
	}
	return (coin);
}

int	line_lenght_checker(t_map *map)
{
	int	i;
	int	first_line;

	i = 0;
	first_line = ft_strlen(map->m_dat[i]);
	while (i < map->height - 2)
	{
		if (ft_strlen(map->m_dat[i]) != (size_t)first_line)
			return (0);
		i++;
	}
	i++;
	if (ft_strlen(map->m_dat[i]) + 1 != (size_t)first_line)
		return (0);
	return (1);
}

int	check_carac(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width - 1)
		{
			if (map->m_dat[i][j] != '1' && map->m_dat[i][j] != '0' && \
				map->m_dat[i][j] != 'P' && map->m_dat[i][j] != 'E' && \
				map->m_dat[i][j] != 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dest;

	if (data->addr)
	{
		dest = data->addr + (y * data->line_length + x * \
		(data->bits_per_pixel / 8));
		*(unsigned int *)dest = color;
	}
	return ;
}

bool	dfs(t_map *map, bool **visited, int x, int y)
{
	static t_point	directions[4] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	static bool		exit = false;
	int				new_x;
	int				new_y;
	int				i;

	i = 0;
	if (map->m_dat[y][x] == 'E')
		exit = true;
	if (map->m_dat[y][x] == 'C' && exit == true)
		return (true);
	visited[y][x] = true;
	while (i < 4)
	{
		new_x = x + directions[i].x;
		new_y = y + directions[i].y;
		if (is_valid_move(map, visited, new_x, new_y))
			if (dfs(map, visited, new_x, new_y))
				return (true);
		i++;
	}
	return (false);
}
