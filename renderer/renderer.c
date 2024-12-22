/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:12:53 by helarras          #+#    #+#             */
/*   Updated: 2024/12/22 12:29:41 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

bool	rnd_draw_map(t_game *game)
{
	int y;
	int x;
	mlx_image_t *space_img;
	mlx_image_t *wall_img;
	
	space_img = gfx_create_image(game, 64, 64, get_rgba(51,175,255,255));
	wall_img = gfx_create_image(game, 64, 64, get_rgba(225, 221, 221, 255));
	if (!space_img || !wall_img)
		return (false);
	y = -1;
	while (game->mapscan->map[++y])
	{
		x = -1;
		while (game->mapscan->map[y][++x])
			if (game->mapscan->map[y][x] == '1')
				mlx_image_to_window(game->mlx, wall_img, x * 64 - 1, y * 64 - 1);
			else if (game->mapscan->map[y][x] == '0')
				mlx_image_to_window(game->mlx, space_img, x * 64  - 1, y * 64 - 1);
	}
	return (true);
}
