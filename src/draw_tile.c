/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:35:35 by jimpa             #+#    #+#             */
/*   Updated: 2025/01/31 15:35:36 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tiles2(t_params p, int x, int y)
{
	int	pixel_x;
	int	pixel_y;

	pixel_x = x * TILE_SIZE * ZOOM_FACTOR;
	pixel_y = y * TILE_SIZE * ZOOM_FACTOR;
	if (p.map->m_dat[y][x] == '0')
		draw_sprite_0(p, pixel_x, pixel_y);
	else if (p.map->m_dat[y][x] == 'P')
		draw_sprite_p(p, pixel_x, pixel_y);
	else if (p.map->m_dat[y][x] == 'D')
		draw_sprite_d(p, pixel_x, pixel_y);
	return ;
}

void	draw_tiles(t_params p, t_point old, t_point new)
{
	draw_tiles2(p, new.x, new.y);
	draw_tiles2(p, old.x, old.y);

}
