/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:15:50 by helarras          #+#    #+#             */
/*   Updated: 2025/03/05 14:13:37 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/world_bonus.h"

t_world	*init_world(mlx_t *mlx, t_colors colors)
{
	t_world *world;

	world = malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	world->mlx = mlx;
	world->graphics = NULL;
	world->colors = colors;
	return (world);
}

t_textures	wd_load_textures(t_world *world, t_texpath texpaths)
{
	t_textures textures;

	// TODO: loading textures.
	textures.north_texture = gfx_create_teximage(world->mlx, world->graphics, texpaths.north_tex);
	textures.east_texture = gfx_create_teximage(world->mlx, world->graphics, texpaths.east_tex);
	textures.south_texture = gfx_create_teximage(world->mlx, world->graphics, texpaths.south_tex);
	textures.west_texture = gfx_create_teximage(world->mlx, world->graphics, texpaths.west_tex);
	
	return (textures);
}
