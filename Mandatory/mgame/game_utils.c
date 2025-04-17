/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:31:47 by helarras          #+#    #+#             */
/*   Updated: 2025/04/17 17:15:05 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

t_mapscan	*readmap(char *mapfile)
{
	t_mapscan	*mapscan;

	mapscan = init_mapscan(mapfile);
	if (!mapscan)
		return (NULL);
	mp_loadmap(mapscan);
	if (!mp_verifymap(mapscan))
	{
		mp_clearmap(mapscan);
		exit(EXIT_FAILURE);
	}
	return (mapscan);
}

bool	load_resources(t_game *game)
{
	if (!wd_load_textures(game->world, game->mapscan->texpaths))
		return (false);
	return (true);
}

void	init_angle(t_game *game)
{
	double angle;
	char c_dir;

	c_dir = game->mapscan->c_direction;
	if (c_dir == 'N')
		angle = radians(270);
	else if (c_dir == 'E')
		angle = radians(0);
	else if (c_dir == 'S')
		angle = radians(90);
	else if (c_dir == 'W')
		angle = radians(180);
	game->player->direction.rotatin_angle = angle;
	
}