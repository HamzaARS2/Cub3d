/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:12:53 by helarras          #+#    #+#             */
/*   Updated: 2024/12/22 13:14:13 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

bool	rnd_draw_map(t_game *game)
{
	int y;
	int x;
	char	**map;
	mlx_image_t *space_img;
	mlx_image_t *wall_img;
	
	map = game->mapscan->map;
	space_img = gfx_create_image(game, TILE_SIZE, TILE_SIZE, get_rgba(225, 221, 221, 255));
	wall_img = gfx_create_image(game, TILE_SIZE, TILE_SIZE, get_rgba(51,175,255,255));
	if (!space_img || !wall_img)
		return (false);
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '1')
				mlx_image_to_window(game->mlx, wall_img, x * TILE_SIZE, y * TILE_SIZE);
			else if (ump_is_mpcomponent(map[y][x]))
				mlx_image_to_window(game->mlx, space_img, x * TILE_SIZE, y * TILE_SIZE);
	}
	return (true);
}

bool	rnd_draw_object(t_game *game, int x, int y)
{
	mlx_image_t *object;

	object = gfx_create_image(game, 16, 16, get_rgba(33, 216, 184, 255));
	if (!object)
		return (false);
	mlx_image_to_window(game->mlx, object, x * TILE_SIZE, y * TILE_SIZE);
	return (true);
}
