/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:07:09 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 12:37:32 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"

t_player	*init_player(t_game *game, mlx_image_t *img, t_point pos)
{
	t_player	*object;

	object = malloc(sizeof(t_player));
	if (!object)
		return (NULL);
	object->position.x = pos.x * TILE_SIZE + (TILE_SIZE / 2) - (OBJ_SIZE / 2);
	object->position.y = pos.y * TILE_SIZE + (TILE_SIZE / 2) - (OBJ_SIZE / 2);
	object->speed = 3.0f;
	object->direction = (t_Dvector){0};
	if (!img)
		object->image = gfx_create_image(game->mlx, &game->world->graphics,
				OBJ_SIZE, OBJ_SIZE);
	else
		object->image = img;
	return (object);
}

void	obj_update_mvdirection(t_game *game, double rotation,
		t_Dvector direction)
{
	double	new_x;
	double	new_y;
	double	distance_x;
	double	distance_y;

	direction.rotatin_angle = normalize_angle(direction.rotatin_angle);
	distance_x = cos(normalize_angle(direction.rotatin_angle + rotation))
		* (direction.walk_direction * game->player->speed);
	distance_y = sin(normalize_angle(direction.rotatin_angle + rotation))
		* (direction.walk_direction * game->player->speed);
	new_x = game->player->position.x - (OBJ_SIZE / 2) + distance_x;
	new_y = game->player->position.y - (OBJ_SIZE / 2) + distance_y;
	if (mv_check_collusion(new_x, new_y, game->mapscan->map, '1')
		&& check_door_collusion(new_x, new_y, game->mapscan->map, game))
		mv_move_player(game->player, new_x, new_y);
	cast_rays(game);
}

bool	draw_player(t_game *game)
{
	t_point		start;
	t_point		end;
	t_player	*player;

	player = game->player;
	start = (t_point){0, 0};
	end = (t_point){OBJ_SIZE, OBJ_SIZE};
	mlx_image_to_window(game->mlx, player->image, MAP_WIDTH / 2, MAP_HEIGHT
		/ 2);
	gfx_draw_rect(player->image, start, end, get_rgba(33, 216, 184, 255));
	board_clean(game->world->drawing_board);
	cast_rays(game);
	return (true);
}
