/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:31:47 by helarras          #+#    #+#             */
/*   Updated: 2025/03/15 16:28:37 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"

t_mapscan	*readmap(char *mapfile)
{
	t_mapscan *mapscan;

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
	if (!anim_load_idle(game->animator, &game->world->graphics))
		 return (false);
	if (!anim_load_attack1(game->animator, &game->world->graphics))
		 return (false);
	if (!anim_load_attack2(game->animator, &game->world->graphics))
		 return (false);
	return (true);
}