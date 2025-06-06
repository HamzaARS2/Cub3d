/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:12:53 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 12:37:14 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"

int	get_color(t_mapscan *mapscan, t_point p)
{
	int	x;
	int	y;

	x = floor((double)p.x / TILE_SIZE);
	y = floor((double)p.y / TILE_SIZE);
	if (x < 0 || x >= mapscan->mapsize.x || y < 0 || y >= mapscan->mapsize.y)
		return (255);
	if (mapscan->map[y][x] == '1')
		return (get_rgba(51, 175, 255, 255));
	if (mapscan->map[y][x] == 'D')
		return (get_rgba(235, 52, 110, 255));
	if (ump_is_mpcomponent(mapscan->map[y][x]))
		return (get_rgba(252, 250, 255, 255));
	return (255);
}

t_point	get_map_offset(t_player *player)
{
	t_point	p;

	p.x = player->position.x - MAP_WIDTH / 2;
	p.y = player->position.y - MAP_HEIGHT / 2;
	return (p);
}

void	draw_minimap(t_game *game)
{
	t_point	p;
	t_point	offset;

	p = (t_point){0};
	offset = get_map_offset(game->player);
	while (p.y < MAP_HEIGHT)
	{
		p.x = 0;
		offset.x = game->player->position.x - MAP_WIDTH / 2;
		while (p.x < MAP_WIDTH)
		{
			if (p.y <= 1 || p.y >= MAP_HEIGHT - 2 || p.x <= 1
				|| p.x >= MAP_WIDTH - 2)
				mlx_put_pixel(game->map_img, p.x, p.y, 255);
			else
				mlx_put_pixel(game->map_img, p.x, p.y, get_color(game->mapscan,
						offset));
			p.x++;
			offset.x++;
		}
		p.y++;
		offset.y++;
	}
}
