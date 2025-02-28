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

	p = (t_point) {0};
	while (p.y < MAP_HEIGHT)
	{
		p.x = 0;
		while (p.x < MAP_WIDTH)
		{
			if (p.y <= 1 || p.y >= MAP_HEIGHT - 2 || p.x <= 1 || p.x >= MAP_WIDTH - 2)
				mlx_put_pixel(game->map_img, p.x, p.y, 255);
			else
				mlx_put_pixel(game->map_img, p.x, p.y, get_rgba(255,255,255,255));
			p.x++;
		}
		p.y++;
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














