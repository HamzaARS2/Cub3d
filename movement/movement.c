/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:28:03 by helarras          #+#    #+#             */
/*   Updated: 2025/01/16 17:08:20 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

void	mv_move_object(t_object *object, int new_x, int new_y)
{
	object->position.x = new_x;
	object->position.y = new_y;
	object->image->instances[0].x = object->position.x;
	object->image->instances[0].y = object->position.y;
}

bool	mv_check_collusion(int new_x, int new_y, char **map, char comp)
{
	t_vector2 top_left;
	t_vector2 top_right;
	t_vector2 bot_left;
	t_vector2 bot_right;

	top_left.x = (new_x + 0) / TILE_SIZE;
	top_left.y = (new_y + 0) / TILE_SIZE;
	top_right.x = (new_x + OBJ_SIZE - 0) / TILE_SIZE;
	top_right.y = (new_y + 0) / TILE_SIZE;
	bot_left.x = (new_x + 0) / TILE_SIZE;
	bot_left.y = (new_y + OBJ_SIZE - 0) / TILE_SIZE;
	bot_right.x = (new_x + OBJ_SIZE - 0) / TILE_SIZE;
	bot_right.y = (new_y + OBJ_SIZE - 0) / TILE_SIZE;
	if (map[top_left.y][top_left.x] == comp
		|| map[top_right.y][top_right.x] == comp
		|| map[bot_left.y][bot_left.x] == comp
		|| map[bot_right.y][bot_right.x] == comp)
		return (false);
	return (true);
}

void	mv_handle_moves(void *param)
{
	t_game *game;
	t_object *player;

	game = param;
	player = game->player;
	player->direction = (t_vector2) {0};
	bresenham_line(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		player->direction.y = -1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		player->direction.y = 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		player->direction.x = 1; 
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		player->direction.x = -1;

	obj_update_mvdirection(game, player);
}
