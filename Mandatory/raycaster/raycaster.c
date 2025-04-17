/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:34:28 by nhimad            #+#    #+#             */
/*   Updated: 2025/04/17 15:34:29 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycaster.h"

t_vector2	vertical_intersection(t_game *game, double ray_angle, int *v_d)
{
	t_data	h_data;

	h_data.hit = (t_vector2){0};
	h_data.player = game->player;
	get_vert_x(&h_data, ray_angle, v_d);
	get_vert_y(&h_data, ray_angle, v_d);
	h_data.hit.x = h_data.px;
	h_data.hit.y = h_data.py;
	find_wall_hit(game, &h_data.hit, h_data.xa, h_data.ya);
	return (h_data.hit);
}

double	get_distance(t_vector2 hit, t_player *player)
{
	return (sqrt(powf(player->position.x - hit.x, 2) + powf(player->position.y
				- hit.y, 2)));
}

t_ray_dat	find_nearest_hit(t_game *game, double ray_angle)
{
	t_vector2	h_hit;
	t_vector2	v_hit;
	t_player	*player;
	int			v_d[2];

	player = game->player;
	vision_dierction(ray_angle, v_d);
	h_hit = horizontal_intersection(game, ray_angle, v_d);
	v_hit = vertical_intersection(game, ray_angle, v_d);
	if (v_hit.y != INVALID_DATA && (h_hit.y == INVALID_DATA
			|| get_distance(h_hit, player) > get_distance(v_hit, player)))
		return (get_ray_data(v_hit, v_d, 'V'));
	return (get_ray_data(h_hit, v_d, 'H'));
}
