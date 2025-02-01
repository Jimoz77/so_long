/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiparcer <jiparcer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:58:34 by jiparcer          #+#    #+#             */
/*   Updated: 2025/02/01 16:59:11 by jiparcer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_s(t_params p, int x, int y, char tile)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = x * TILE_SIZE * ZOOM_FACTOR;
	pixel_y = y * TILE_SIZE * ZOOM_FACTOR;
	if (tile == '1')
		draw_sprite_1(p, pixel_x, pixel_y);
	else if (tile == '0')
		draw_sprite_0(p, pixel_x, pixel_y);
	else if (tile == 'P')
		draw_sprite_p(p, pixel_x, pixel_y);
	else if (tile == 'E')
		draw_sprite_e(p, pixel_x, pixel_y);
	else if (tile == 'C')
		draw_sprite_c(p, pixel_x, pixel_y);
	else if (tile == 'D')
		draw_sprite_d(p, pixel_x, pixel_y);
}

static void	draw_map_line(t_params p, int y)
{
	int	x;

	x = 0;
	while (x < p.map->width)
	{
		draw_s(p, x, y, p.map->m_dat[y][x]);
		x++;
	}
}

void	draw_map(t_params p)
{
	int	y;

	y = 0;
	while (y < p.map->height)
	{
		draw_map_line(p, y);
		y++;
	}
}
