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
	int x;
	int y;

	x = p.x / TILE_SIZE;
	y = p.y / TILE_SIZE;
	// HARD CODE
	if (x < 0 || x >= 32 || y < 0 || y >= 15)
		return (0);
	if (map[y][x] == '1')
		return get_rgba(255, 0, 0, 255);
	if (ump_is_mpcomponent(map[y][x]))
		return get_rgba(0, 255, 0, 255);
	return (0);
}



t_point	get_map_offset(t_object *player)
{
	t_point p;

	p.x = player->position.x - MAP_WIDTH / 2;
	p.y = player->position.y - MAP_HEIGHT / 2;
	if (p.x < 0)
		p.x = 0;
	if (p.y < 0)
		p.y = 0;
	return p;
}

bool    rnd_draw_map(t_game *game)
{
    int x;
    int y;
    char    **map;
    mlx_image_t *image;
    
    map = game->mapscan->map;
    image = gfx_create_image(game, WIDTH, HEIGHT);
    mlx_image_to_window(game->mlx, image, 0, 0);
    
    y = -1;
    while (map[++y])
    {
        x = -1;
        while (map[y][++x])
            if (map[y][x] == '1')
                gfx_set_color(image,(t_point) {x, y}, get_rgba(51,175,255,255));
            else if (ump_is_mpcomponent(map[y][x]))
                gfx_set_color(image,(t_point) {x, y} , get_rgba(225, 221, 221, 255));
    }
    return (true);
}

void rnd_draw_minimap(t_game *game)
{
	t_point p;
	t_point offset;

	p = (t_point) {0};
	offset = get_map_offset(game->player);
	while (p.y < MAP_HEIGHT)
	{
		p.x = 0;
		offset.x = game->player->position.x - MAP_WIDTH / 2;
		// if (offset.x < 0) offset.x = 0;
		while (p.x < MAP_WIDTH)
		{
			if (p.y <= 1 || p.y >= MAP_HEIGHT - 2 || p.x <= 1 || p.x >= MAP_WIDTH - 2)
				mlx_put_pixel(game->map_img, p.x, p.y, 255);
			else
				mlx_put_pixel(game->map_img, p.x, p.y, get_color(game->mapscan->map, offset));
			p.x++;
			offset.x++;
		}
		p.y++;
		offset.y++;
	}
}

bool	rnd_draw_player(t_game *game)
{
	// t_point pos;

	// pos = game->player->position;
	// game->player->position.x += (OBJ_SIZE / 2);
	// game->player->position.y += (OBJ_SIZE / 2);
	mlx_image_to_window(game->mlx, game->player->image, MAP_WIDTH / 2, MAP_HEIGHT / 2);
	board_clean(game->drawing_board);
	cast_rays(game);
	return (true);
}














