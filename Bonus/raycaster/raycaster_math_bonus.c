/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_math_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:41:42 by nhimad            #+#    #+#             */
/*   Updated: 2025/04/19 12:16:55 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycaster_bonus.h"

void	get_hori_y(t_data *data, int *v_d)
{
	if (v_d[0] == looking_up)
	{
		data->py = floor(data->player->position.y / TILE_SIZE) * TILE_SIZE
			- NEXT_T;
		data->ya = -TILE_SIZE;
	}
	else
	{
		data->py = floor(data->player->position.y / TILE_SIZE) * TILE_SIZE
			+ TILE_SIZE + NEXT_T;
		data->ya = TILE_SIZE;
	}
}

void	geth_hori_x(t_data *data, double ray_angle, int *v_d)
{
	data->xa = fabs(data->ya / tan(ray_angle));
	if (v_d[1] == looking_right)
		data->px = data->player->position.x + fabs((data->py
					- data->player->position.y) / tan(ray_angle)) - NEXT_T;
	else
	{
		data->px = data->player->position.x - fabs((data->py
					- data->player->position.y) / tan(ray_angle)) + NEXT_T;
		data->xa *= -1;
	}
}

t_vector2	horizontal_intersection(t_game *game, double ray_angle, int *v_d)
{
	t_data	h_data;

	h_data.hit = (t_vector2){0};
	game->door.door_ray.hitp = (t_vector2){-1, -1};
	h_data.player = game->player;
	get_hori_y(&h_data, v_d);
	geth_hori_x(&h_data, ray_angle, v_d);
	h_data.hit.x = h_data.px;
	h_data.hit.y = h_data.py;
	find_wall_hit(game, &h_data.hit, h_data.xa, h_data.ya);
	return (h_data.hit);
}

void	get_vert_x(t_data *data, int *v_d)
{
	if (v_d[1] == looking_right)
	{
		data->px = floor(data->player->position.x / TILE_SIZE) * TILE_SIZE
			+ TILE_SIZE + NEXT_T;
		data->xa = TILE_SIZE;
	}
	else
	{
		data->px = floor(data->player->position.x / TILE_SIZE) * TILE_SIZE
			- NEXT_T;
		data->xa = -TILE_SIZE;
	}
}

void	get_vert_y(t_data *data, double ray_angle, int *v_d)
{
	data->ya = fabs(data->xa * tan(ray_angle));
	if (v_d[0] == looking_down)
		data->py = data->player->position.y + fabs((data->player->position.x
					- data->px) * tan(ray_angle)) - NEXT_T;
	else
	{
		data->py = data->player->position.y - fabs((data->player->position.x
					- data->px) * tan(ray_angle)) + NEXT_T;
		data->ya *= -1;
	}
}
