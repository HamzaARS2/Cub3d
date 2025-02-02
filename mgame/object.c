/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:07:09 by helarras          #+#    #+#             */
/*   Updated: 2025/01/27 17:59:39 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

t_object	*init_object(t_game *game, mlx_image_t *img ,t_vector2 pos)
{
	t_object *object;

	object = malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	object->position.x = pos.x * TILE_SIZE;
	object->position.y = pos.y * TILE_SIZE;
	object->direction.rotatin_angle = 0;
	object->speed = 5.0f;
	object->direction = (t_Dvector) {0};
	if (!img)
		object->image = gfx_create_image(game, OBJ_SIZE, OBJ_SIZE);
	else
		object->image = img;
	return (object);
}

void	cast_rays(t_game *game)
{
	double	rotate_angle;
	double	rotate_spead;
	float 	degree;

	degree = 0.25;
	rotate_spead = RADIANS(degree);
	board_clean(game->drawing_board);
	rotate_angle = game->player->direction.rotatin_angle;
	game->player->direction.rotatin_angle -= RADIANS(30);
	while (rotate_spead < RADIANS(60))
	{
		bresenham_line(game);
		game->player->direction.rotatin_angle += RADIANS(degree);
		rotate_spead += RADIANS(degree);
	}
	game->player->direction.rotatin_angle = rotate_angle;
}

void	obj_update_mvdirection(t_game *game, int rotation)
{
	t_Dvector *direction;
	double speed;
	double new_x;
	double new_y;
	direction = &(game->player->direction);
	
	speed = game->player->speed;
	direction->rotatin_angle += direction->turnDirection * (ROTATION_SPEED);
	double distance_x = cos(direction->rotatin_angle  + (rotation * (M_PI / 180))) * (direction->walkDirection * speed);
	double distance_y = sin(direction->rotatin_angle  + (rotation * (M_PI / 180))) * (direction->walkDirection * speed);
		
	new_x = round(game->player->position.x + distance_x);
	new_y = round(game->player->position.y + distance_y);
	if (!mv_check_collusion(new_x, new_y, game->mapscan->map, '1')) {
		cast_rays(game);	
		return ;
	}
	mv_move_object(game->player, new_x, new_y);
	cast_rays(game);
}
