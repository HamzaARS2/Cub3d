/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:28:03 by helarras          #+#    #+#             */
/*   Updated: 2025/04/17 18:04:09 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"

void	mv_move_player(t_player *object, double new_x, double new_y)
{
	object->position.x = new_x + (OBJ_SIZE / 2);
	object->position.y = new_y + (OBJ_SIZE / 2);
}

bool	mv_check_collusion(int new_x, int new_y, char **map, char c)
{
	t_point	top_left;
	t_point	top_right;
	t_point	bot_left;
	t_point	bot_right;

	top_left.x = (new_x - (OBJ_SIZE / 2) - 2) / TILE_SIZE;
	top_left.y = (new_y - (OBJ_SIZE / 2) - 2) / TILE_SIZE;
	top_right.x = (new_x + (OBJ_SIZE / 2) + 2) / TILE_SIZE;
	top_right.y = (new_y - (OBJ_SIZE / 2) - 2) / TILE_SIZE;
	bot_left.x = (new_x - (OBJ_SIZE / 2) - 2) / TILE_SIZE;
	bot_left.y = (new_y + (OBJ_SIZE / 2) + 2) / TILE_SIZE;
	bot_right.x = (new_x + (OBJ_SIZE / 2) + 2) / TILE_SIZE;
	bot_right.y = (new_y + (OBJ_SIZE / 2) + 2) / TILE_SIZE;
	if (map[top_left.y][top_left.x] == c || map[top_right.y][top_right.x] == c
		|| map[bot_left.y][bot_left.x] == c
		|| map[bot_right.y][bot_right.x] == c)
		return (false);
	return (true);
}

void	ft_rotate(t_game *game)
{
	t_player	*player;
	double		angle;

	player = game->player;
	angle = player->direction.rotatin_angle;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		player->direction.rotatin_angle = normalize_angle(angle
				- radians(ROTATION_SPEED));
		cast_rays(game);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		player->direction.rotatin_angle = normalize_angle(angle
				+ radians(ROTATION_SPEED));
		cast_rays(game);
	}
}

void	ft_side_mv(t_game *game)
{
	t_player	*player;

	player = game->player;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		player->direction.walk_direction = 1;
		obj_update_mvdirection(game, radians(90), player->direction);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		player->direction.walk_direction = -1;
		obj_update_mvdirection(game, radians(90), player->direction);
	}
}

void	mv_handle_moves(t_game *game)
{
	t_player	*player;

	player = game->player;
	player->direction.walk_direction = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		player->direction.walk_direction = 1;
		obj_update_mvdirection(game, 0, player->direction);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		player->direction.walk_direction = -1;
		obj_update_mvdirection(game, 0, player->direction);
	}
	ft_side_mv(game);
	ft_rotate(game);
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
		anim_set_state(game->animator, ATTACK1);
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_RIGHT))
		anim_set_state(game->animator, ATTACK2);
}
