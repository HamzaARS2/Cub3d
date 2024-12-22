/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:09:35 by helarras          #+#    #+#             */
/*   Updated: 2024/12/22 11:56:13 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "/Users/helarras/MLX42/include/MLX42/MLX42.h"
#include "mapscan.h"

#define WIDTH 2048
#define HEIGHT 960

typedef struct s_graphic {
	mlx_image_t *image;
	bool		is_texture;
} t_graphic;

typedef struct s_game {
	t_mapscan	*mapscan;
	mlx_t		*mlx;
	t_list		*graphics;
} t_game;


bool	init_game(t_game *game, char *mapfile);
void	run_game(t_game *game);
void	cleanup_game(t_game game);

// graphics manager
mlx_image_t	*gfx_create_teximage(t_game *game, char *tex_path);
mlx_image_t	*gfx_create_image(t_game *game, int width, int height, int color);
void	gfx_set_color(mlx_image_t *image, int color);
// renderer
bool	rnd_draw_map(t_game *game);

// utils
t_mapscan	*readmap(char *mapfile);


#endif