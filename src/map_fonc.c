/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fonc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:22:17 by jimpa             #+#    #+#             */
/*   Updated: 2025/01/31 16:59:53 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	are_collectibles_reachable(t_map *map)
{
    bool **visited;
    int	player_x;
    int	player_y;
    int	i = 0;
    int	j;

	visited = (bool **)malloc(map->height * sizeof(bool *));
    if (!is_player(map, &player_x, &player_y))
        return (false);
    if (!visited)
        return (false);

    while (i < map->height)
    {
        visited[i] = (bool *)malloc(map->width * sizeof(bool));
        if (!visited[i])
        {
            while (i-- > 0)
                free(visited[i]);
            free(visited);
            return (false);
        }
        j = 0;
        while (j < map->width)
        {
            visited[i][j] = false;
            j++;
        }
        i++;
    }

    i = 0;
    while (i < map->height)
    {
        j = 0;
        while (j < map->width)
        {
            if (map->m_dat[i][j] == 'C')
            {
                int k = 0;
                while (k < map->height)
                {
                    int l = 0;
                    while (l < map->width)
                    {
                        visited[k][l] = false;
                        l++;
                    }
                    k++;
                }
                if (!dfs(map, visited, player_x, player_y, j, i))
                {
                    k = 0;
                    while (k < map->height)
                    {
                        free(visited[k]);
                        k++;
                    }
                    free(visited);
                    return (false);
                }
            }
            j++;
        }
        i++;
    }

    i = 0;
    while (i < map->height)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
    return (true);
}

bool	is_map_solvable(t_map *map)
{
    bool result;
    bool **visited;
    int player_x, player_y;
    int exit_x = -1, exit_y = -1;
    int i = 0, j;

	visited = (bool **)malloc(map->height * sizeof(bool *));
    if (!is_player(map, &player_x, &player_y))
        return (false);
    if (!visited)
        return (false);

    while (i < map->height)
    {
        visited[i] = (bool *)malloc(map->width * sizeof(bool));
        if (!visited[i])
        {
            while (i-- > 0)
                free(visited[i]);
            free(visited);
            return false;
        }
        j = 0;
        while (j < map->width)
        {
            visited[i][j] = false;
            if (map->m_dat[i][j] == 'E')
            {
                exit_x = j;
                exit_y = i;
            }
            j++;
        }
        i++;
    }

    if (exit_x == -1 || exit_y == -1)
    {
        i = 0;
        while (i < map->height)
        {
            free(visited[i]);
            i++;
        }
        free(visited);
        return false;
    }

    result = dfs(map, visited, player_x, player_y, exit_x, exit_y);

    i = 0;
    while (i < map->height)
    {
        free(visited[i]);
        i++;
    }
    free(visited);
    return result;
}

int	check_map_corners(t_map *map)
{
	int	x;
	int	y;
	int	y_max;

	x = 0;
	y = 0;
	while (x < (map->width - 1))
	{
		if (map->m_dat[0][x] != '1')
			return (0);
		x++;
	}
	while (y < map->height - 1)
	{
		if (map->m_dat[y][0] != '1')
			return (0);
		y++;
	}
	y_max = y;
	x--;
	while (y >= 0)
	{
		if (map->m_dat[y][x] != '1')
			return (0);
		y--;
	}
	while (x >= 0)
	{
		if (map->m_dat[y_max][x] != '1')
			return (0);
		x--;
	}
	return (1);
}

void	draw_map(t_params p)
{
	int	x;
	int	y;
	int	pixel_x;
	int	pixel_y;

	y = 0;
	while (y < p.map->height)
	{
		x = 0;
		while (x < p.map->width)
		{
			pixel_x = x * TILE_SIZE * ZOOM_FACTOR;
			pixel_y = y * TILE_SIZE * ZOOM_FACTOR;
			if (p.map->m_dat[y][x] == '1')
				draw_sprite_1(p, pixel_x, pixel_y);
			else if (p.map->m_dat[y][x] == '0')
				draw_sprite_0(p, pixel_x, pixel_y);
			else if (p.map->m_dat[y][x] == 'P')
				draw_sprite_p(p, pixel_x, pixel_y);
			else if (p.map->m_dat[y][x] == 'E')
				draw_sprite_e(p, pixel_x, pixel_y);
			else if (p.map->m_dat[y][x] == 'C')
				draw_sprite_c(p, pixel_x, pixel_y);
			else if (p.map->m_dat[y][x] == 'D')
				draw_sprite_d(p, pixel_x, pixel_y);
			x++;
		}
		y++;
	}
}

t_map	*read_map(char *file_name)
{
	t_map	*map;
	char	*line;
	int		fd;
	int		i;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = 0;
	while ((line = get_next_line(fd)))
	{
		free(line);
		map->height++;
	}
	map->m_dat = (char **)malloc(sizeof(char *) * map->height);
	if (!map->m_dat)
	{
		free(map);
		return (NULL);
	}
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		free(map->m_dat);
		free(map);
		return (NULL);
	}
	i = 0;
	while ((line = get_next_line(fd)))
	{
		map->m_dat[i] = line;
		i++;
	}
	if (map->height > 0)
		map->width = ft_strlen(map->m_dat[0]);
	else
		map->width = 0;
	close(fd);
	return (map);
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
