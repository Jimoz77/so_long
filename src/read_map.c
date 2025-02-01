/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:42:50 by jiparcer          #+#    #+#             */
/*   Updated: 2025/02/01 17:18:38 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_map_height(char *file_name)
{
	char	*line;
	int		fd;
	int		height;

	height = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		height++;
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static bool	allocate_map_memory(t_map *map)
{
	map->m_dat = (char **)malloc(sizeof(char *) * map->height);
	if (!map->m_dat)
	{
		free(map);
		return (false);
	}
	return (true);
}

static bool	read_map_data(t_map *map, char *file_name)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		map->m_dat[i++] = line;
		line = get_next_line(fd);
	}
	close(fd);
	if (map->height > 0)
		map->width = ft_strlen(map->m_dat[0]);
	else
		map->width = 0;
	return (true);
}

t_map	*read_map(char *file_name)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = get_map_height(file_name);
	if (map->height < 0 || !allocate_map_memory(map) \
	|| !read_map_data(map, file_name))
	{
		free(map->m_dat);
		free(map);
		return (NULL);
	}
	return (map);
}
