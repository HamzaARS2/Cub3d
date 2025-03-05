/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:21:46 by helarras          #+#    #+#             */
/*   Updated: 2025/03/05 13:21:02 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"

void handle_cursor_movement(double xpos, double ypos, void* param);

bool	 init_game(t_game *game, char *mapfile)
{
	mlx_image_t *obj_img;
	
	game->mapscan = readmap(mapfile);
	if (!game->mapscan)
		return (false);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		return (false);
	game->mouse_pos = game->mapscan->start_pos;
	game->world = init_world(game->mlx, game->mapscan->colors);
	game->player = init_player(game, NULL, game->mapscan->start_pos);
	game->drawing_board = gfx_create_image(game->mlx, game->world->graphics, WIDTH, HEIGHT);
	game->map_img = gfx_create_image(game->mlx, game->world->graphics, MAP_WIDTH, MAP_HEIGHT);
	return (true);
}


void	run_game(t_game *game)
{
	wd_load_textures(game->world, game->mapscan->texpaths);
	mlx_image_to_window(game->mlx, game->drawing_board, 0, 0);
	mlx_image_to_window(game->mlx, game->map_img, 0, 0);
	draw_player(game);
	// mlx_cursor_hook(game->mlx, handle_cursor_movement, game);
	mlx_loop_hook(game->mlx, update, game);
	// mlx_image_to_window(game->mlx, game->textures.north_texture, WIDTH / 2, 0);


	//printf("mapszie: widthx: %i | heighty: %i\n", game->mapscan->mapsize.x, game->mapscan->mapsize.y);
	// game loop.
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}

void handle_cursor_movement(double xpos, double ypos, void* param)
{
	// t_game *game;
	// double angle;
	// int x_d;

	// //mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	// game = param;
	// angle = game->player->direction.rotatin_angle;
	// x_d = xpos - game->mouse_pos.x;
	// angle = normalizeAngle(angle + x_d * 0.15);
	// game->player->direction.rotatin_angle = angle;
	// game->mouse_pos.x = xpos;
	// game->mouse_pos.y = -1;
	//printf("xpos: %f-----mpx: %d \n", xpos, game->mouse_pos.x);
	
}

void	update(void *param) {
	t_game	*game;
	mlx_t	*mlx;
	
	game = param;
	mlx = game->mlx;
	// handling moving objects
	
	// if (game->mouse_pos.y == -1)
	// {
	// 	game->mouse_pos.y = 0;
	// 	cast_rays(game);
	// }
	mv_handle_moves(game);
	draw_minimap(game);
	// mlx_get_mouse_pos(mlx, &game->mouse_pos.x, &game->mouse_pos.y);
	// game->mouse_pos.x -= game->player->position.x;
	// game->mouse_pos.y -= game->player->position.y;
}

void	cleanup_game(t_game game)
{
	mp_clearmap(game.mapscan);
}