/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:12:53 by helarras          #+#    #+#             */
/*   Updated: 2025/02/24 16:07:48 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

void	set_color(mlx_image_t *img, t_point start, t_point end, int color)
{
	int x;
	int y;

	y = start.y;
	while (y < end.y)
	{
		x = start.x;
		while (x < end.x)
			mlx_put_pixel(img, x++, y, color);
		y++;
	}
}

int	get_color(char **map, t_point p)
{
	if (p.x / TILE_SIZE >= 32) return (0);
	if (p.y / TILE_SIZE >= 15) return (0);
	if (map[p.y / TILE_SIZE][p.x / TILE_SIZE] == '1')
		return get_rgba(51, 175, 255, 255);
	else if (ump_is_mpcomponent(map[p.y / TILE_SIZE][p.x / TILE_SIZE]))
		return get_rgba(225, 221, 221, 255);
	return (0);
}


t_point	get_map_offset(t_object *player)
{
	t_point p;

	p.x = player->position.x - 52;
	p.y = player->position.y - 52;
	if (p.x < 0)
		p.x = 0;
	if (p.y < 0)
		p.y = 0;
	return p;
}

bool	rnd_draw_map(t_game *game)
{
	t_point pp;
	t_point offset;
	char	**map;
	t_point pencil;
	
	map = game->mapscan->map;
	pp = game->player->position;
	offset = get_map_offset(game->player);
	pencil.y = 0;
	while (pencil.y < MAP_HEIGHT)
	{
		pencil.x = 0;
		offset.x = game->player->position.x - 52;
		while(pencil.x < MAP_WIDTH)
		{
			mlx_put_pixel(game->map_img, pencil.x, pencil.y, get_color(game->mapscan->map, offset));
			offset.x++;
			pencil.x++;
		}
		offset.y++;
		pencil.y++;
	}
	return (true);
}

bool	rnd_draw_player(t_game *game)
{
	t_point pos;

	pos = game->player->position;
	game->player->position.x += (OBJ_SIZE / 2);
	game->player->position.y += (OBJ_SIZE / 2);
	mlx_image_to_window(game->mlx, game->player->image, pos.x, pos.y);
	board_clean(game->drawing_board);
	cast_rays(game);
	return (true);
}














