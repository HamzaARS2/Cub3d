/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:21:46 by helarras          #+#    #+#             */
/*   Updated: 2025/02/24 16:07:55 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

bool	 init_game(t_game *game, char *mapfile)
{
	mlx_image_t *obj_img;
	
	game->graphics = NULL;
	game->mapscan = readmap(mapfile);
	if (!game->mapscan)
		return (false);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		return (false);
	game->mouse_pos = game->mapscan->start_pos;
	game->player = init_object(game, NULL, game->mapscan->start_pos);
	// virtual player
	game->vplayer = gfx_create_image(game, OBJ_SIZE, OBJ_SIZE);
	gfx_set_color(game->player->image, (t_point){0} , get_rgba(33, 216, 184, 255));
	game->drawing_board = gfx_create_image(game, WIDTH, HEIGHT);
	game->map_img = gfx_create_image(game, MAP_WIDTH, MAP_HEIGHT);
	return (true);
}


void	run_game(t_game *game)
{
	rnd_draw_map(game);
	mlx_image_to_window(game->mlx, game->map_img, 0, 0);
	mlx_image_to_window(game->mlx, game->drawing_board, 0, 0);
	rnd_draw_player(game);
	// virtual player
	mlx_image_to_window(game->mlx, game->vplayer, game->mapscan->start_pos.x, game->mapscan->start_pos.y);
	mlx_loop_hook(game->mlx, update, game);
	// game loop.
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

void	update(void *param) {
	t_game	*game;
	mlx_t	*mlx;
	
	game = param;
	mlx = game->mlx;
	// handling moving objects
	
	mv_handle_moves(game);
	rnd_draw_minimap(game);
	// mlx_get_mouse_pos(mlx, &game->mouse_pos.x, &game->mouse_pos.y);
	// game->mouse_pos.x -= game->player->position.x;
	// game->mouse_pos.y -= game->player->position.y;
}

void	cleanup_game(t_game game)
{
	mp_clearmap(game.mapscan);
}