/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_helper_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:44:45 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 13:06:04 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"
#include "../include/raycaster_bonus.h"
#include "../include/world_bonus.h"

static void	wd_init_textures(t_world *world)
{
	ft_memset(&world->textures.north_texture, 0, sizeof(t_wd_texture));
	ft_memset(&world->textures.east_texture, 0, sizeof(t_wd_texture));
	ft_memset(&world->textures.south_texture, 0, sizeof(t_wd_texture));
	ft_memset(&world->textures.west_texture, 0, sizeof(t_wd_texture));
	ft_memset(&world->textures.door_texture, 0, sizeof(t_wd_texture));
}

bool	wd_load_textures(t_world *world, t_texpath texpaths)
{
	wd_init_textures(world);
	world->crosshair = gfx_create_teximage(world->mlx, &world->graphics, CP);
	if (!world->crosshair)
		return (false);
	world->textures.north_texture.img = gfx_create_teximage(world->mlx,
			&world->graphics, texpaths.north_tex);
	if (!world->textures.north_texture.img)
		return (false);
	world->textures.east_texture.img = gfx_create_teximage(world->mlx,
			&world->graphics, texpaths.east_tex);
	if (!world->textures.east_texture.img)
		return (false);
	world->textures.south_texture.img = gfx_create_teximage(world->mlx,
			&world->graphics, texpaths.south_tex);
	if (!world->textures.south_texture.img)
		return (false);
	world->textures.west_texture.img = gfx_create_teximage(world->mlx,
			&world->graphics, texpaths.west_tex);
	if (!world->textures.west_texture.img)
		return (false);
	world->textures.door_texture.img = gfx_create_teximage(world->mlx,
			&world->graphics, "Bonus/textures/doors/door.png");
	if (!world->textures.door_texture.img)
		return (false);
	return (true);
}

void	wd_prepare_colors(t_world *world)
{
	world->textures.north_texture.pixels = wd_get_color_buffer
		(world->textures.north_texture.img);
	world->textures.east_texture.pixels = wd_get_color_buffer
		(world->textures.east_texture.img);
	world->textures.south_texture.pixels = wd_get_color_buffer
		(world->textures.south_texture.img);
	world->textures.west_texture.pixels = wd_get_color_buffer
		(world->textures.west_texture.img);
	world->textures.door_texture.pixels = wd_get_color_buffer
		(world->textures.door_texture.img);
}
