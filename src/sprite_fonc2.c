/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_fonc2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:02:41 by jimpa             #+#    #+#             */
/*   Updated: 2025/01/31 14:40:13 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_zoomed_pixel(t_params p, t_draw_params dp)
{
	dp.draw.dy = 0;
	while (dp.draw.dy < ZOOM_FACTOR)
	{
		dp.draw.dx = 0;
		while (dp.draw.dx < ZOOM_FACTOR)
		{
			if ((dp.start_y + dp.draw.y * ZOOM_FACTOR + dp.draw.dy) < 1080 \
			&& (dp.start_x + dp.draw.x * ZOOM_FACTOR + dp.draw.dx) < 1920)
			{
				my_mlx_pixel_put(p.img, dp.start_x + dp.draw.x * ZOOM_FACTOR + \
				dp.draw.dx, dp.start_y + dp.draw.y * ZOOM_FACTOR + dp.draw.dy, \
				dp.draw.color);
			}
			dp.draw.dx++;
		}
		dp.draw.dy++;
	}
}

void	draw_sprite(t_params p, int start_x, int start_y, t_sprite_params sp)
{
	t_draw_params	dp;
	t_draw			draw;

	dp.start_x = start_x;
	dp.start_y = start_y;
	draw.y = 0;
	while (draw.y < TILE_SIZE)
	{
		draw.x = 0;
		while (draw.x < TILE_SIZE)
		{
			if ((sp.sprite_y + draw.y) < p.sprite->height && \
			(sp.sprite_x + draw.x) < p.sprite->width)
			{
				draw.pixel = p.sprite->addr + ((sp.sprite_y + draw.y) * \
				p.sprite->width + (sp.sprite_x + draw.x)) * 4;
				draw.color = *(unsigned int *)draw.pixel;
				dp.draw = draw;
				draw_zoomed_pixel(p, dp);
			}
			draw.x++;
		}
		draw.y++;
	}
}

void	draw_sprite_d(t_params p, int start_x, int start_y)
{
	t_sprite_params	sp;

	sp.sprite_x = SPRITE_EXIT_DONE_X;
	sp.sprite_y = SPRITE_EXIT_DONE_Y;
	draw_sprite(p, start_x, start_y, sp);
}

void	draw_sprite_e(t_params p, int start_x, int start_y)
{
	t_sprite_params	sp;

	sp.sprite_x = SPRITE_EXIT_X;
	sp.sprite_y = SPRITE_EXIT_Y;
	draw_sprite(p, start_x, start_y, sp);
}

void	draw_sprite_c(t_params p, int start_x, int start_y)
{
	t_sprite_params	sp;

	sp.sprite_x = SPRITE_COIN_X;
	sp.sprite_y = SPRITE_COIN_Y;
	draw_sprite(p, start_x, start_y, sp);
}
