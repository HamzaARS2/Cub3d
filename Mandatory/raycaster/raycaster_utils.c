/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:34:25 by nhimad            #+#    #+#             */
/*   Updated: 2025/04/17 15:36:57 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycaster.h"

double	radians(double angle)
{
	return (angle * (M_PI / 180));
}

int	check_wall(t_game *game, t_vector2 *hitp, char **map, t_point map_size)
{
	int	x_tile;
	int	y_tile;

	x_tile = (hitp->x / TILE_SIZE);
	y_tile = (hitp->y / TILE_SIZE);
	if (isinf(hitp->y) || isinf(hitp->x))
		hitp->y = INVALID_DATA;
	else if ((int)hitp->y < 0 || (int)hitp->x < 0)
		hitp->y = INVALID_DATA;
	else if (y_tile >= map_size.y || x_tile >= map_size.x)
		hitp->y = INVALID_DATA;
	else if (map[y_tile][x_tile] == 0)
		hitp->y = INVALID_DATA;
	if (hitp->y == INVALID_DATA || map[y_tile][x_tile] == '1')
		return (0);
	return (1);
}

void	vision_dierction(double angel, int *v_d)
{
	if (angel > M_PI)
		v_d[0] = looking_up;
	else
		v_d[0] = looking_down;
	if (angel > M_PI_2 && angel < 1.5 * M_PI)
		v_d[1] = looking_left;
	else
		v_d[1] = looking_right;
}

void	find_wall_hit(t_game *game, t_vector2 *hit, double Xa, double Ya)
{
	char	**map;
	t_point	map_size;

	map = game->mapscan->map;
	map_size = game->mapscan->mapsize;
	while (check_wall(game, hit, map, map_size))
	{
		hit->x = hit->x + Xa;
		hit->y = hit->y + Ya;
	}
}

t_ray_dat	get_ray_data(t_vector2 hit, int *v_d, char c)
{
	t_ray_dat	ray_dat;

	ray_dat.hitp = hit;
	if (c == 'V')
	{
		ray_dat.ver_hor = c;
		if (v_d[1] == looking_left)
			ray_dat.direction = 'W';
		else
			ray_dat.direction = 'E';
	}
	else if (c == 'H')
	{
		ray_dat.ver_hor = c;
		if (v_d[0] == looking_up)
			ray_dat.direction = 'N';
		else
			ray_dat.direction = 'S';
	}
	return (ray_dat);
}
