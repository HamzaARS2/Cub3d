/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:07:09 by helarras          #+#    #+#             */
/*   Updated: 2025/04/17 18:04:09 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

t_player	*init_player(t_game *game, mlx_image_t *img, t_point pos)
{
	t_player	*object;

	object = malloc(sizeof(t_player));
	if (!object)
		return (NULL);
	object->position.x = pos.x * TILE_SIZE + (TILE_SIZE / 2) - (OBJ_SIZE / 2);
	object->position.y = pos.y * TILE_SIZE + (TILE_SIZE / 2) - (OBJ_SIZE / 2);
	object->speed = 2.0f;
	object->direction = (t_Dvector){};
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
	if (mv_check_collusion(new_x, new_y, game->mapscan->map, '1'))
		mv_move_player(game->player, new_x, new_y);
	cast_rays(game);
}

bool	draw_player(t_game *game)
{
	board_clean(game->world->drawing_board);
	cast_rays(game);
	return (true);
}
