/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fonc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:18:14 by jimpa             #+#    #+#             */
/*   Updated: 2025/01/27 18:12:10 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_params2(t_params *params)
{
	if (params->sprite)
	{
		if (params->sprite->img)
			mlx_destroy_image(params->mlx_ptr, params->sprite->img);
		free(params->sprite);
	}
	if (params->win_ptr)
		mlx_destroy_window(params->mlx_ptr, params->win_ptr);
	if (params->mlx_ptr)
	{
		mlx_destroy_display(params->mlx_ptr);
		free(params->mlx_ptr);
	}
}

void	free_params(t_params *params)
{
	int	i;

	i = 0;
	if (params)
	{
		if (params->map)
		{
			while (i < params->map->height)
			{
				free(params->map->m_dat[i]);
				i++;
			}
			free(params->map->m_dat);
			free(params->map);
		}
		if (params->img)
		{
			if (params->img->img)
				mlx_destroy_image(params->mlx_ptr, params->img->img);
			free(params->img);
		}
		free_params2(params);
	}
}

int	close_win_cross(t_params *param)
{
	free_params(param);
	exit(0);
	return (0);
}
