/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_renderer_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:41:53 by nhimad            #+#    #+#             */
/*   Updated: 2025/04/19 12:20:59 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycaster_bonus.h"

void	board_clean(mlx_image_t *drawing_board)
{
	unsigned int	color;
	int				x;
	int				y;

	y = -1;
	x = -1;
	color = 0x00000000;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			mlx_put_pixel(drawing_board, x, y, color);
	}
}

double	normalize_angle(double angle)
{
	double	two_pi;

	two_pi = 2 * M_PI;
	while (angle < 0)
		angle += two_pi;
	while (angle >= two_pi)
		angle -= two_pi;
	return (angle);
}

void	render_doors(t_game *game)
{
	if (game->door.closed || (game->door.close_cmd
			&& mv_check_collusion(game->player->position.x,
				game->player->position.y, game->mapscan->map, 'D')))
	{
		wd_render_doors(game->world, game->door.door_ray);
		game->door.closed = true;
	}
	else if (!game->door.closed && game->door.door_ray.distance > TILE_SIZE * 5
		&& mv_check_collusion(game->player->position.x,
			game->player->position.y, game->mapscan->map, 'D'))
		game->door.closed = true;
	else if (!game->door.closed)
	{
		game->door.close_cmd = false;
		return ;
	}
}

void	send_ray(t_game *game, int x, double angle)
{
	t_player	*player;
	t_vector2	hit;
	t_ray_dat	ray_dat;
	double		ray_angle;

	player = game->player;
	ray_angle = normalize_angle(game->player->direction.rotatin_angle + angle);
	ray_dat = find_nearest_hit(game, ray_angle);
	game->door.door_ray.current_column = x;
	ray_dat.current_column = x;
	hit = ray_dat.hitp;
	ray_dat.distance = get_distance(hit, player) * cos(angle);
	game->door.door_ray.distance = get_distance(game->door.door_ray.hitp,
			player) * cos(angle);
	if (ray_dat.distance < game->door.door_ray.distance)
		game->door.door_ray.hitp.x = INVALID_DATA;
	if (game->door.door_ray.hitp.x != INVALID_DATA)
		render_doors(game);
	wd_render_walls(game->world, ray_dat);
}

void	cast_rays(t_game *game)
{
	double	rotate_angle;
	double	ray_angle;
	double	angle_shift;
	int		x;

	x = 0;
	ray_angle = radians((FOV / 2) * -1);
	angle_shift = ((double)radians(FOV) / WIDTH);
	board_clean(game->world->door_img);
	board_clean(game->world->drawing_board);
	rotate_angle = game->player->direction.rotatin_angle;
	while (ray_angle < radians(30) && x < WIDTH)
	{
		send_ray(game, x, ray_angle);
		ray_angle += angle_shift;
		x++;
	}
	game->player->direction.rotatin_angle = rotate_angle;
}
