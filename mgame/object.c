/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:07:09 by helarras          #+#    #+#             */
/*   Updated: 2025/01/26 16:30:42 by nhimad           ###   ########.fr       */
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
	object->speed = 120.0f;
	object->direction = (t_Dvector) {0};
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
	double dt = game->mlx->delta_time;
	direction = &(game->player->direction);
	
	speed = game->player->speed * dt;
	direction->rotatin_angle += direction->turnDirection * (ROTATION_SPEED);
	double distance_x = cos(direction->rotatin_angle  + (rotation * (M_PI / 180))) * (direction->walkDirection * speed);
	double distance_y = sin(direction->rotatin_angle  + (rotation * (M_PI / 180))) * (direction->walkDirection * speed);
	
	printf("distance_x: %f | distance_y %f\n", distance_x, distance_y);
	
	new_x = game->player->position.x + distance_x;
	new_y = game->player->position.y + distance_y;
	if (!mv_check_collusion(round(new_x), round(new_y), game->mapscan->map, '1'))
		return ;
	game->player->position.x = round(new_x);
	game->player->position.y = round(new_y);;
	printf("ra: %f, x: %f, y: %f\n", direction->rotatin_angle, new_x, new_y);
	bresenham_line(game);
	game->player->image->instances[0].x = game->player->position.x;
	game->player->image->instances[0].y = game->player->position.y;
}
