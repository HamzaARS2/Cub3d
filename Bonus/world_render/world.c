/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:15:50 by helarras          #+#    #+#             */
/*   Updated: 2025/03/03 14:12:37 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/world_render_bonus.h"

t_world	*init_world(t_colors colors, t_texpath texpaths)
{
	t_world *world;

	world = malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	world->colors = colors;
	world->textures = wd_load_textures(texpaths);
	return (world);
}

t_textures	wd_load_textures(t_texpath texpaths)
{
	t_textures textures;

	// TODO: loading textures.
	return (textures);
}