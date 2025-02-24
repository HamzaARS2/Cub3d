/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:09:35 by helarras          #+#    #+#             */
/*   Updated: 2025/02/24 14:16:16 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "mapscan.h"

#define WIDTH 1200
#define HEIGHT 1300

#define TILE_SIZE 32
#define OBJ_SIZE 4
#define ROTATION_SPEED 2
# define RADIANS(d) (d * (M_PI / 180))

typedef struct s_Dvector  {
	double 		x;
	double 		y;
	char 		turnDirection;
	char 		walkDirection;
	double		rotatin_angle;		
} t_Dvector;

typedef struct s_vector2 {
	double x;
	double y;
} t_vector2;

typedef struct s_object {
	mlx_image_t	*image;
	t_vector2	position;
	t_Dvector	direction;
	float		speed;
} t_object;

typedef struct s_game {
	t_mapscan	*mapscan;
	mlx_t		*mlx;
	t_list		*graphics;
	t_object	*player;
	t_point	mouse_pos;
	mlx_image_t *drawing_board;
} t_game;


void	bresenham_line(t_game *game, int *x, double angle);

bool	init_game(t_game *game, char *mapfile);
void	run_game(t_game *game);
void	update(void *param);
void	cleanup_game(t_game game);

// graphics manager
mlx_image_t	*gfx_create_teximage(t_game *game, char *tex_path);
mlx_image_t	*gfx_create_image(t_game *game, int width, int height);
void	gfx_set_color(mlx_image_t *image, t_point coords, int color);
// renderer
bool	rnd_draw_map(t_game *game);
bool	rnd_draw_player(t_game *game);
// movements
void	mv_move_object(t_object *object, int new_x, int new_y);
void	mv_handle_moves(t_game *game);
bool	mv_check_collusion(int new_x, int new_y, char **map, char comp);
// object
t_object	*init_object(t_game *game, mlx_image_t *img ,t_point pos);
void	obj_update_mvdirection(t_game *game, int rotation);

// utils
t_mapscan	*readmap(char *mapfile);
void	board_clean(mlx_image_t *drawing_board);

void	cast_rays(t_game *game);

double normalizeAngle(double angle);

#endif
