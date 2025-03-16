/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:21:46 by helarras          #+#    #+#             */
/*   Updated: 2025/03/15 16:29:09 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

bool	 init_game(t_game *game, char *mapfile)
{
	mlx_image_t *obj_img;
	
	game->mapscan = readmap(mapfile);
	if (!game->mapscan)
		return (false);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		return (false);
	game->world = init_world(game->mlx, game->mapscan->colors);
	game->player = init_player(game, NULL, game->mapscan->start_pos);
	game->animator = init_animator(game->mlx, true);
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
	anim_play(game->animator);
	// game loop.
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

void	update(void *param) {
	t_game	*game;
	mlx_t	*mlx;
	
	game = param;
	mlx = game->mlx;
	
	anim_update(game->animator);
	anim_render(game->animator);
	mv_handle_moves(game);
}

void	cleanup_game(t_game game)
{
	mp_clearmap(game.mapscan);
	wd_clear(game.world);
	free(game.player);
	free(game.animator);
}