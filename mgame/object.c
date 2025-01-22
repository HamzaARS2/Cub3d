/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:07:09 by helarras          #+#    #+#             */
/*   Updated: 2025/01/22 12:06:47 by helarras         ###   ########.fr       */
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
	object->speed = 8.0f;
	object->direction = (t_vector2) {0};
	if (!img)
		object->image = gfx_create_image(game, OBJ_SIZE, OBJ_SIZE);
	else
		object->image = img;
	return (object);
}

void	obj_update_mvdirection(t_game *game, t_object *object)
{
	float speed;
	int new_x;
	int new_y;

	if (object->direction.x != 0 && object->direction.y != 0)
		speed = object->speed * 0.707;
	else
		speed = object->speed;
	new_x = object->position.x + object->direction.x * speed;
	new_y = object->position.y + object->direction.y * speed;
	if (!mv_check_collusion(new_x, new_y, game->mapscan->map, '1'))
		return ;
	mv_move_object(object, new_x, new_y);
}
