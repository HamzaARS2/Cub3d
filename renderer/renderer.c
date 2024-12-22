/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:12:53 by helarras          #+#    #+#             */
/*   Updated: 2024/12/22 14:04:36 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

bool	rnd_draw_map(t_game *game)
{
	t_vector2 v2;
	char	**map;
	mlx_image_t *space_img;
	mlx_image_t *wall_img;
	
	map = game->mapscan->map;
	space_img = gfx_create_image(game, TILE_SIZE, TILE_SIZE, get_rgba(225, 221, 221, 255));
	wall_img = gfx_create_image(game, TILE_SIZE, TILE_SIZE, get_rgba(51,175,255,255));
	if (!space_img || !wall_img)
		return (false);
	v2.y = -1;
	while (map[++v2.y])
	{
		v2.x = -1;
		while (map[v2.y][++v2.x])
			if (map[v2.y][v2.x] == '1')
				mlx_image_to_window(game->mlx, wall_img, v2.x * TILE_SIZE, v2.y * TILE_SIZE);
			else if (ump_is_mpcomponent(map[v2.y][v2.x]))
				mlx_image_to_window(game->mlx, space_img, v2.x * TILE_SIZE, v2.y * TILE_SIZE);
	}
	return (true);
}

bool	rnd_draw_object(t_game *game, t_vector2 v2)
{
	mlx_image_t *object;

	object = gfx_create_image(game, 16, 16, get_rgba(33, 216, 184, 255));
	if (!object)
		return (false);
	mlx_image_to_window(game->mlx, object, v2.x * TILE_SIZE, v2.y * TILE_SIZE);
	return (true);
}
