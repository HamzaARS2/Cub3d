/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:21:46 by helarras          #+#    #+#             */
/*   Updated: 2024/12/20 08:47:02 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"



bool	init_game(t_game *game, char *mapfile)
{
	game->mapscan = readmap(mapfile);
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	if (!game->mlx)
		return (false);
	
	return (true);
}


void	run_game(t_game *game)
{
	
	// game loop.
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}


void	cleanup_game(t_game game)
{
	mp_clearmap(game.mapscan);
}