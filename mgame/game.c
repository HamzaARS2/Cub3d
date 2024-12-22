/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:21:46 by helarras          #+#    #+#             */
/*   Updated: 2024/12/22 12:56:34 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"



bool	init_game(t_game *game, char *mapfile)
{
	game->mapscan = readmap(mapfile);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!game->mlx)
		return (false);
	
	return (true);
}


void	run_game(t_game *game)
{
	rnd_draw_map(game);
	rnd_draw_object(game, 12, 10);
	// game loop.
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}


void	cleanup_game(t_game game)
{
	mp_clearmap(game.mapscan);
}