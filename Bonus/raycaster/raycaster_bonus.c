/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:41:37 by nhimad            #+#    #+#             */
/*   Updated: 2025/04/17 16:41:38 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycaster_bonus.h"

t_vector2	vertical_intersection(t_game *game, double ray_angle, int *v_d)
{
	t_data	h_data;

	h_data.hit = (t_vector2){0};
	game->door.door_ray.hitp = (t_vector2){-1};
	h_data.player = game->player;
	get_vert_x(&h_data, ray_angle, v_d);
	get_vert_y(&h_data, ray_angle, v_d);
	h_data.hit.x = h_data.px;
	h_data.hit.y = h_data.py;
	find_wall_hit(game, &h_data.hit, h_data.xa, h_data.ya);
	return (h_data.hit);
}

void	get_door_ray(t_game *game, t_player *player, t_vector2 h_hit,
		t_vector2 v_hit)
{
	double	h_door_dist;
	double	v_door_dist;

	h_door_dist = get_distance(h_hit, player);
	v_door_dist = get_distance(v_hit, player);
	if (h_hit.x != INVALID_DATA && (v_hit.x == INVALID_DATA
			|| h_door_dist < v_door_dist))
	{
		game->door.door_ray.hitp = h_hit;
		game->door.door_ray.ver_hor = 'H';
	}
	else if (v_hit.x != INVALID_DATA && (h_hit.x == INVALID_DATA
			|| v_door_dist < h_door_dist))
	{
		game->door.door_ray.hitp = v_hit;
		game->door.door_ray.ver_hor = 'V';
	}
}

double	get_distance(t_vector2 hit, t_player *player)
{
	return (sqrt(powf(player->position.x - hit.x, 2) + powf(player->position.y
				- hit.y, 2)));
}

t_ray_dat	find_nearest_hit(t_game *game, double ray_angle)
{
	t_vector2	h_hit[2];
	t_vector2	v_hit[2];
	t_player	*player;
	int			v_d[2];

	player = game->player;
	vision_dierction(ray_angle, v_d);
	h_hit[0] = horizontal_intersection(game, ray_angle, v_d);
	h_hit[1] = game->door.door_ray.hitp;
	v_hit[0] = vertical_intersection(game, ray_angle, v_d);
	v_hit[1] = game->door.door_ray.hitp;
	get_door_ray(game, player, h_hit[1], v_hit[1]);
	if (v_hit[0].y != INVALID_DATA && (h_hit[0].y == INVALID_DATA
			|| get_distance(h_hit[0], player) > get_distance(v_hit[0], player)))
		return (get_ray_data(v_hit[0], v_d, 'V'));
	return (get_ray_data(h_hit[0], v_d, 'H'));
}
