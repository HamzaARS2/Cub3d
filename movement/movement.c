/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:28:03 by helarras          #+#    #+#             */
/*   Updated: 2025/02/24 14:15:44 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

void	mv_move_object(t_object *object, int new_x, int new_y)
{
	object->position.x = new_x + (OBJ_SIZE / 2);
	object->position.y = new_y + (OBJ_SIZE / 2);
	// object->image->instances[0].x = new_x;
	// object->image->instances[0].y = new_y;
}

bool	mv_check_collusion(int new_x, int new_y, char **map, char comp)
{
	t_point top_left;
	t_point top_right;
	t_point bot_left;
	t_point bot_right;

	top_left.x = (new_x - 1) / TILE_SIZE;
	top_left.y = (new_y - 1) / TILE_SIZE;
	top_right.x = (new_x + OBJ_SIZE + 1) / TILE_SIZE;
	top_right.y = (new_y - 1) / TILE_SIZE;
	bot_left.x = (new_x - 1) / TILE_SIZE;
	bot_left.y = (new_y + OBJ_SIZE + 1) / TILE_SIZE;
	bot_right.x = (new_x + OBJ_SIZE + 1) / TILE_SIZE;
	bot_right.y = (new_y + OBJ_SIZE + 1) / TILE_SIZE;
	if (map[top_left.y][top_left.x] == comp
		|| map[top_right.y][top_right.x] == comp
		|| map[bot_left.y][bot_left.x] == comp
		|| map[bot_right.y][bot_right.x] == comp)
		return (false);
	return (true);
}

void	mv_handle_moves(t_game *game)
{
	t_object *player;

	player = game->player;
	player->direction.turnDirection = 0;
	player->direction.walkDirection = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{	
		player->direction.walkDirection = 1;
		obj_update_mvdirection(game, 0);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{	
		player->direction.walkDirection = -1;
		obj_update_mvdirection(game, 0);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{	
		player->direction.walkDirection = 1;
		obj_update_mvdirection(game, 90);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{	
		player->direction.walkDirection = -1;
		obj_update_mvdirection(game, 90);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		player->direction.rotatin_angle -= ROTATION_SPEED;
		cast_rays(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		player->direction.rotatin_angle += ROTATION_SPEED;
		cast_rays(game);
	}
}
