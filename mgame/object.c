/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:07:09 by helarras          #+#    #+#             */
/*   Updated: 2025/02/10 17:47:47 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

t_object	*init_object(t_game *game, mlx_image_t *img ,t_vector2 pos)
{
	t_object *object;

	object = malloc(sizeof(t_object));
	if (!object)
		return (NULL);
	object->position.x = pos.x * TILE_SIZE + (TILE_SIZE / 2) - (OBJ_SIZE / 2);;
	object->position.y = pos.y * TILE_SIZE + (TILE_SIZE / 2) - (OBJ_SIZE / 2);;
	object->speed = 3.0f;
	object->direction = (t_Dvector) {0};
	//object->direction.rotatin_angle = 270;
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
	double 	angle_shift;
	int x;

	// printf("x: %f, y: %f\n", game->player->position.x, game->player->position.y);
	x = 0;
	rotate_spead = -30;
	angle_shift = ((double)60 / WIDTH );
	// printf("ang: %f, angle_sh: %f\n", game->player->direction.rotatin_angle, angle_shift);
	board_clean(game->drawing_board);
	rotate_angle = game->player->direction.rotatin_angle;
	game->player->direction.rotatin_angle = normalizeAngle(game->player->direction.rotatin_angle + rotate_spead);
	while (rotate_spead <= 30)
	{
		// printf("/////cast angle : %f\n", game->player->direction.rotatin_angle);
		bresenham_line(game, &x, rotate_spead);
		game->player->direction.rotatin_angle = normalizeAngle(game->player->direction.rotatin_angle +  angle_shift);
		rotate_spead += angle_shift;
		x++;
	}
	game->player->direction.rotatin_angle = rotate_angle;
	// printf("ang: %f\n", game->player->direction.rotatin_angle);
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
		
	new_x = round(game->player->position.x + distance_x);
	new_y = round(game->player->position.y + distance_y);
	if (!mv_check_collusion(new_x, new_y, game->mapscan->map, '1')) {
		cast_rays(game);	
		return ;
	}
	mv_move_object(game->player, new_x, new_y);
	cast_rays(game);
}
