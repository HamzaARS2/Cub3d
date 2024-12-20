/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:09:35 by helarras          #+#    #+#             */
/*   Updated: 2024/12/20 08:42:23 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "/Users/helarras/MLX42/include/MLX42/MLX42.h"
#include "mapscan.h"

#define WIDTH 600
#define HEIGHT 400

typedef struct s_game {
	t_mapscan	*mapscan;
	mlx_t		*mlx;
} t_game;


bool	init_game(t_game *game, char *mapfile);
void	run_game(t_game *game);
void	cleanup_game(t_game game);


// utils
t_mapscan	*readmap(char *mapfile);


#endif