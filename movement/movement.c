/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:28:03 by helarras          #+#    #+#             */
/*   Updated: 2024/12/22 16:56:37 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

void	mv_move_object(t_object *object, t_vector2 velocity)
{
	
	object->position.x += velocity.x;
	object->position.y += velocity.y;
	object->image->instances[0].x += velocity.x;
	object->image->instances[0].y += velocity.y;
	
}

bool	mv_check_collusion(t_object *object, char **map, char comp)
{
	t_vector2 top_left;
	t_vector2 top_right;
	t_vector2 bot_left;
	t_vector2 bot_right;

	top_left.x = object->position.x / TILE_SIZE;
	top_left.y = object->position.y / TILE_SIZE;
	
	top_right.x = object->position.x / TILE_SIZE;
	top_right.y = object->position.y / TILE_SIZE;

	bot_left.x = object->position.x / TILE_SIZE;
	bot_left.y = object->position.y / TILE_SIZE;
	
	bot_right.x = object->position.x / TILE_SIZE;
	bot_right.y = object->position.y / TILE_SIZE;
	if (map[top_left.y][top_left.x] == comp || map[top_right.x][top_right.y]
		|| map[bot_left.y][bot_left.x] == comp || map[bot_right.y][bot_right.x] == comp)
		return (false);
	return (true);
}
void	mv_handle_moves(void *param)
{
	t_game *game;
	t_object *player;

	game = param;
	player = game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		mv_move_object(player, (t_vector2) {0, -player->velocity});
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		mv_move_object(player, (t_vector2) {0, player->velocity});
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		mv_move_object(player, (t_vector2) {player->velocity, 0});
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		mv_move_object(player, (t_vector2) {-player->velocity, 0});
	printf("x %i y %i | \n", player->position.x, player->position.y);
}