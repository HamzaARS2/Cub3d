/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:21:46 by helarras          #+#    #+#             */
/*   Updated: 2025/01/16 16:56:23 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

bool	init_game(t_game *game, char *mapfile)
{
	mlx_image_t *obj_img;
	
	game->graphics = NULL;
	game->mapscan = readmap(mapfile);
	if (!game->mapscan)
		return (false);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		return (false);
	game->player = init_object(game, NULL, game->mapscan->start_pos);
	gfx_set_color(game->player->image, (t_vector2){0} , get_rgba(33, 216, 184, 255));
	return (true);
}


void	run_game(t_game *game)
{
	rnd_draw_map(game);
	rnd_draw_player(game);	
	mlx_loop_hook(game->mlx, mv_handle_moves, game);
	// game loop.
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}


void	cleanup_game(t_game game)
{
	mp_clearmap(game.mapscan);
}