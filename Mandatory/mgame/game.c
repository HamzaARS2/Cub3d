/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:21:46 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 11:35:25 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

bool	init_game(t_game *game, char *mapfile)
{
	ft_memset(game, 0, sizeof(t_game));
	game->mapscan = readmap(mapfile);
	if (!game->mapscan)
		return (false);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		return (false);
	game->world = init_world(game->mlx, game->mapscan->colors);
	game->player = init_player(game, NULL, game->mapscan->start_pos);
	init_angle(game);
	if (!load_resources(game))
		return (false);
	return (true);
}

void	run_game(t_game *game)
{
	wd_prepare_colors(game->world);
	mlx_image_to_window(game->mlx, game->world->cf_img, 0, 0);
	mlx_image_to_window(game->mlx, game->world->drawing_board, 0, 0);
	wd_render_cf(game->world);
	draw_player(game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

void	update(void *param)
{
	t_game	*game;
	mlx_t	*mlx;

	game = param;
	mlx = game->mlx;
	mv_handle_moves(game);
}

void	cleanup_game(t_game game)
{
	mp_clearmap(game.mapscan);
	wd_clear(game.world);
	free(game.player);
}
