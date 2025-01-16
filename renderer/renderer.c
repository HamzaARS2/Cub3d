/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:12:53 by helarras          #+#    #+#             */
/*   Updated: 2025/01/16 17:09:04 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

bool	rnd_draw_map(t_game *game)
{
	int x;
	int y;
	char	**map;
	mlx_image_t *map_img;
	
	map = game->mapscan->map;
	map_img = gfx_create_image(game, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, map_img, 0, 0);
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			if (map[y][x] == '1')
				gfx_set_color(map_img,(t_vector2) {x, y}, get_rgba(51,175,255,255));
			else if (ump_is_mpcomponent(map[y][x]))
				gfx_set_color(map_img,(t_vector2) {x, y} , get_rgba(225, 221, 221, 255));
	}
	return (true);
}

bool	rnd_draw_player(t_game *game)
{
	t_vector2 pos;

	pos = game->player->position;
	mlx_image_to_window(game->mlx, game->player->image, pos.x, pos.y);
	return (true);
}