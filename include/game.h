/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:09:35 by helarras          #+#    #+#             */
/*   Updated: 2025/01/25 12:44:35 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "/Users/nhimad/Desktop/MLX42/include/MLX42/MLX42.h"
#include "mapscan.h"

#define WIDTH 2048
#define HEIGHT 1024

#define TILE_SIZE 64
#define OBJ_SIZE 8
#define ROTATION_SPEED (2.5 * (M_PI / 180))

typedef struct s_Dvector  {
	double 		x;
	double 		y;
	char 		turnDirection;
	char 		walkDirection;
	double		rotatin_angle;		
} t_Dvector;

typedef struct s_vector3 {
	double x;
	double y;
	double z;
} t_vector3;

typedef struct s_object {
	mlx_image_t	*image;
	t_vector3	position;
	t_Dvector	direction;
	float		speed;
} t_object;

typedef struct s_game {
	t_mapscan	*mapscan;
	mlx_t		*mlx;
	t_list		*graphics;
	t_object	*player;
	mlx_image_t *drawing_board;
} t_game;


void	bresenham_line(t_game *game);

bool	init_game(t_game *game, char *mapfile);
void	run_game(t_game *game);
void	cleanup_game(t_game game);

// graphics manager
mlx_image_t	*gfx_create_teximage(t_game *game, char *tex_path);
mlx_image_t	*gfx_create_image(t_game *game, int width, int height);
void	gfx_set_color(mlx_image_t *image, t_vector2 coords, int color);
// renderer
bool	rnd_draw_map(t_game *game);
bool	rnd_draw_player(t_game *game);
// movements
void	mv_handle_moves(void *param);
bool	mv_check_collusion(int new_x, int new_y, char **map, char comp);
// object
t_object	*init_object(t_game *game, mlx_image_t *img ,t_vector2 pos);
void	obj_update_mvdirection(t_game *game, t_object *object);

// utils
t_mapscan	*readmap(char *mapfile);
void	board_clean(mlx_image_t *drawing_board);

#endif
