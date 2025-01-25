/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:07:09 by helarras          #+#    #+#             */
/*   Updated: 2025/01/25 12:32:32 by nhimad           ###   ########.fr       */
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
	object->speed = 3.0f;
	object->direction = (t_Dvector) {0};
	if (!img)
		object->image = gfx_create_image(game, OBJ_SIZE, OBJ_SIZE);
	else
		object->image = img;
	return (object);
}

void	obj_update_mvdirection(t_game *game, t_object *object)
{
	t_Dvector *direction;
	double speed;
	double new_x;
	double new_y;

	direction = &object->direction;
	// if (object->direction.x != 0 && object->direction.y != 0)
	// 	speed = object->speed * 0.707;
	// else
		speed = object->speed;
	direction->rotatin_angle += direction->turnDirection * (ROTATION_SPEED);
	new_x = object->position.x + cos(direction->rotatin_angle) * (object->direction.x * speed);
	new_y = object->position.y + sin(direction->rotatin_angle) * (object->direction.y * speed);
	if (!mv_check_collusion(round(new_x), round(new_y), game->mapscan->map, '1'))
		return ;
	object->position.x = new_x;
	object->position.y = new_y;
	printf("ra: %f, x: %f, y: %f\n", direction->rotatin_angle, new_x, new_y);
	object->image->instances[0].x = round(object->position.x);
	object->image->instances[0].y = round(object->position.y);
}
