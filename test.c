/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:26:44 by jimpa             #+#    #+#             */
/*   Updated: 2025/01/08 21:32:39 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dest;
	dest = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

int	close_win_esc(int keycode, void *mlx_ptr, void *win_ptr)
{
	if (keycode == 53 || keycode == 65307)
	{
		mlx_destroy_window(mlx_ptr, win_ptr);
		exit(0);
	}
	return (0);
}
int	close_win_cross(void *mlx_ptr, void *win_ptr)
{
	mlx_destroy_window(mlx_ptr, win_ptr);
	exit(0);
	return (0);
}

t_sprite *load_sprite(void *mlx, char *file_path)
{
	t_sprite *sprite;
	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if(!sprite)
		return (NULL);
	sprite->img = mlx_xpm_file_to_image(mlx, file_path, &sprite->width, &sprite->height);
	if (!sprite->img)
		return (NULL);
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->width, &sprite->height, &sprite->width);
	return (sprite);
}





t_map	*read_map(char *file_name)
{
	int		fd;
	char	*line;
	t_map	*map;
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
	map->map_data = (char **)malloc(sizeof(char *) * map->height);
	if (!map->map_data)
		return(NULL);
	close(fd);
	fd = open(file_name, O_RDONLY);
	if(fd < 0)
	return (NULL);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		map->map_data[i] = line;
		i++;
	}
	if (map->height > 0)
		map->width = ft_strlen(map->map_data[0]);
	else
		map->width = 0;
	close(fd);
	return map;
}
void	draw_sprite(t_data *img, t_sprite *sprite, int start_x, int start_y, int sprite_x, int sprite_y, int sprite_width, int sprite_height)
{
	int x;
	int y;
	y = 0;
	char *pixel;
	int color;
	while(y < sprite_height)
	{
		x = 0;
		while (x < sprite_width)
		{
			pixel = sprite->addr + ((sprite_y + y) * sprite->width + (sprite_x + x)) * 4;
			color = *(unsigned int *)pixel;
			my_mlx_pixel_put(img, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_map *map, t_data *img, t_sprite *sprite)
{
	int x;
	int y;
	int pixel_x;
	int pixel_y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			pixel_x = x * tile_size;
			pixel_y = y * tile_size;
			if (map->map_data[y][x] == '1')
				draw_sprite(img, sprite, pixel_x, pixel_y, sprite_wall_x, sprite_wall_y, tile_size, tile_size);
			else if(map->map_data[y][x] == '0')
				draw_sprite(img, sprite, pixel_x, pixel_y, sprite_floor_x, sprite_floor_y, tile_size, tile_size);
			else if (map->map_data[y][x] == 'P')
				draw_sprite(img, sprite, pixel_x, pixel_y, sprite_player_x, sprite_player_y, tile_size, tile_size);
			else if (map->map_data[y][x] == 'E')
				draw_sprite(img, sprite, pixel_x, pixel_y, sprite_exit_x, sprite_exit_y, tile_size, tile_size);
			else if (map->map_data[y][x] == 'C')
				draw_sprite(img, sprite, pixel_x, pixel_y, sprite_coin_x, sprite_coin_y, tile_size, tile_size);
			x++;
		}
		y++;
	}
}






























int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_map	*map;
	t_sprite *sprite;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "maincraft");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	sprite = load_sprite(mlx, "spritesheet.so_long.xpm");

	map = read_map("map.txt");
	draw_map(map, &img, sprite);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	
	mlx_key_hook(mlx_win, (int (*)(void *))close_win_esc, mlx);
	mlx_hook(mlx_win, 33, (1L << 17), (int(*)(void *))close_win_cross, mlx);
	mlx_loop(mlx);
}
