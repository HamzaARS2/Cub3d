/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:21:46 by helarras          #+#    #+#             */
/*   Updated: 2025/03/15 14:14:27 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

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
	game->world = init_world(game->mlx, game->mapscan->colors);
	game->player = init_player(game, NULL, game->mapscan->start_pos);
	game->map_img = gfx_create_image(game->mlx, &game->world->graphics, MAP_WIDTH, MAP_HEIGHT);
	game->animator = init_animator(game->mlx, true);
	bool	is_loaded;
	
	is_loaded = wd_load_textures(game->world, game->mapscan->texpaths);
	if (!is_loaded)
		 return (false);
	is_loaded = anim_load_idle(game->animator, &game->world->graphics);
	if (!is_loaded)
		 return (false);
	is_loaded = anim_load_attack1(game->animator, &game->world->graphics);
	if (!is_loaded)
		 return (false);
	is_loaded = anim_load_attack2(game->animator, &game->world->graphics);
	if (!is_loaded)
		 return (false);
	return (true);
}


void	run_game(t_game *game)
{
	
	wd_prepare_colors(game->world);
	mlx_image_to_window(game->mlx, game->world->cf_img, 0, 0);
	mlx_image_to_window(game->mlx, game->world->drawing_board, 0, 0);
	mlx_image_to_window(game->mlx, game->map_img, 0, 0);
	wd_render_cf(game->world);
	draw_player(game);
	mlx_cursor_hook(game->mlx, handle_cursor_movement, game);
	mlx_loop_hook(game->mlx, update, game);
	anim_play(game->animator);
	// game loop.
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
void handle_cursor_movement(double xpos, double ypos, void* param)
{
	t_game *game;
	double angle;
	int x_d;

	game = param;
	// mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	angle = game->player->direction.rotatin_angle;
	x_d = xpos - game->mouse_pos.x;
	angle = normalizeAngle(angle + x_d * 0.0015);
	game->player->direction.rotatin_angle = angle;
	game->mouse_pos.x = xpos;
	game->mouse_pos.y = -1;
	//printf("xpos: %f-----mpx: %d \n", xpos, game->mouse_pos.x);
	
}

void	update(void *param) {
	t_game	*game;
	mlx_t	*mlx;
	
	game = param;
	mlx = game->mlx;
	
	if (game->mouse_pos.y == -1)
	{
		game->mouse_pos.y = 0;
		cast_rays(game);
	}
	anim_update(game->animator);
	anim_render(game->animator);
	mv_handle_moves(game);
	draw_minimap(game);
}

void	cleanup_game(t_game game)
{
	mp_clearmap(game.mapscan);
	wd_clear(game.world);
	free(game.player);
	free(game.animator);
}