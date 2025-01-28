/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimpa <jimpa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:19:54 by jimpa             #+#    #+#             */
/*   Updated: 2025/01/27 18:12:26 by jimpa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_sprite	*load_sprite(void *mlx, char *file_path)
{
	t_sprite	*sprite;

	sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (!sprite)
		return (NULL);
	sprite->img = mlx_xpm_file_to_image(mlx, file_path, \
	&sprite->width, &sprite->height);
	if (!sprite->img)
	{
		free(sprite);
		return (NULL);
	}
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel, \
	&sprite->line_length, &sprite->endian);
	return (sprite);
}

void	error_case2(t_params *params, int c)
{
	if ((c == 5) && !params->img->addr)
	{
		ft_printf("Error\nErreur lors de l'accès aux données de l'image\n");
		free_params(params);
		exit (1);
	}
	else if ((c == 6) && !params->sprite)
	{
		ft_printf("Error\nErreur lors du chargement du sprite\n");
		free_params(params);
		exit (1);
	}
	else if ((c == 0) && !params->map)
	{
		ft_printf("Error\nAucune map n'as ete donne en argument\n");
		free_params(params);
		exit (0);
	}
	return ;
}

void	error_case(t_params *params, int c)
{
	if ((c == 1) && !params->mlx_ptr)
	{
		ft_printf("Error\nErreur lors de l'initialisation de mlx\n");
		free_params(params);
		exit (0);
	}
	else if ((c == 2) && !params->win_ptr)
	{
		ft_printf("Error\nErreur lors de la création de la fenêtre\n");
		free_params(params);
		exit (1);
	}
	else if ((c == 3) && !params->img)
	{
		ft_printf("Error\nErreur d'allocation de mémoire pour l'image\n");
		free_params(params);
		exit (1);
	}
	else if ((c == 4) && !params->img->img)
	{
		ft_printf("Error\nErreur lors de la création de l'image\n");
		free_params(params);
		exit (1);
	}
	return (error_case2(params, c));
}

t_params	init_params(t_params params, char **av)
{
	params.map = read_map(av[1]);
	error_case(&params, 0);
	params.max_coin = coin_counter(params.map);
	map_checker(&params);
	params.mlx_ptr = mlx_init();
	error_case(&params, 1);
	params.win_ptr = mlx_new_window(params.mlx_ptr, 1920, 1080, "so_long");
	error_case(&params, 2);
	params.img = malloc(sizeof(t_data));
	error_case(&params, 3);
	params.img->img = mlx_new_image(params.mlx_ptr, 1920, 1080);
	error_case(&params, 4);
	params.img->addr = mlx_get_data_addr(params.img->img, \
	&params.img->bits_per_pixel, &params.img->line_length, \
	&params.img->endian);
	error_case(&params, 5);
	params.sprite = load_sprite(params.mlx_ptr, "spritesheet.so_long.xpm");
	error_case(&params, 6);
	return (params);
}

int	main(int ac, char **av)
{
	t_params	params;

	ft_memset(&params, 0, sizeof(t_params));
	params.zoom = 3;
	if (ac == 2)
	{
		params = init_params(params, av);
		draw_map(params);
		mlx_put_image_to_window(params.mlx_ptr, params.win_ptr, \
		params.img->img, 0, 0);
		mlx_key_hook(params.win_ptr, key_input, &params);
		mlx_hook(params.win_ptr, 33, (1L << 17), close_win_cross, &params);
		mlx_loop(params.mlx_ptr);
	}
	else
		ft_printf("Error\nAucune map n'as ete donne en argument\n");
	return (0);
}
