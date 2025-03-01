/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:07:09 by helarras          #+#    #+#             */
/*   Updated: 2025/03/01 11:00:26 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

t_player	*init_player(t_game *game, mlx_image_t *img ,t_point pos)
{
	t_player *object;

	object = malloc(sizeof(t_player));
	if (!object)
		return (NULL);
	object->position.x = pos.x * TILE_SIZE + (TILE_SIZE / 2) - (OBJ_SIZE / 2);
	object->position.y = pos.y * TILE_SIZE + (TILE_SIZE / 2) - (OBJ_SIZE / 2);
	object->speed = 3.0f;
	object->direction = (t_Dvector) {0};
	//object->direction.rotatin_angle = 270;
	if (!img)
		object->image = gfx_create_image(game, OBJ_SIZE, OBJ_SIZE);
	else
		object->image = img;
	return (object);
}

void	obj_update_mvdirection(t_game *game, int rotation)
{
	t_Dvector *direction;
	double speed;
	double new_x;
	double new_y;
	direction = &(game->player->direction);
	
	speed = game->player->speed;
	//direction->rotatin_angle += direction->turnDirection * ROTATION_SPEED;
	direction->rotatin_angle = normalizeAngle(direction->rotatin_angle);
	double distance_x = cos(RADIANS(normalizeAngle(direction->rotatin_angle + rotation))) * (direction->walkDirection * speed);
	double distance_y = sin(RADIANS(normalizeAngle(direction->rotatin_angle + rotation))) * (direction->walkDirection * speed);
		
	new_x = round(game->player->position.x - (OBJ_SIZE / 2) + distance_x);
	new_y = round(game->player->position.y - (OBJ_SIZE / 2) + distance_y);
	if (mv_check_collusion(new_x, new_y, game->mapscan->map, '1'))
		mv_move_player(game->player, new_x, new_y);
	cast_rays(game);
}

bool	draw_player(t_game *game)
{
	mlx_image_to_window(game->mlx, game->player->image, MAP_WIDTH / 2, MAP_HEIGHT / 2);
	board_clean(game->drawing_board);
	cast_rays(game);
	return (true);
}
