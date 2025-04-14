/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:09:35 by helarras          #+#    #+#             */
/*   Updated: 2025/03/15 16:27:52 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "../../MLX42/include/MLX42/MLX42.h"
#include "mapscan.h"
#include "gfx_manager.h"
#include "world.h"

#define WIDTH 1440
#define HEIGHT 800

#define MAP_WIDTH 300
#define MAP_HEIGHT 250

#define ROTATION_SPEED 2
# define radians(d) (d * (M_PI / 180))


typedef struct s_Dvector  {
	double 		x;
	double 		y;
	char 		turnDirection;
	char 		walkDirection;
	double		rotatin_angle;		
} t_Dvector;


typedef struct s_player {
	mlx_image_t	*image;
	t_vector2	position;
	t_Dvector	direction;
	double		speed;
} t_player;

typedef struct s_game {
	t_mapscan	*mapscan;
	t_world		*world;
	mlx_t		*mlx;
	t_player	*player;
} t_game;


void	bresenham_line(t_game *game, int x, double angle);

bool	init_game(t_game *game, char *mapfile);
void	run_game(t_game *game);
void	update(void *param);
void	cleanup_game(t_game game);

// renderer
bool	draw_player(t_game *game);

// movements
void	mv_move_player(t_player *object, double new_x, double new_y);
void	mv_handle_moves(t_game *game);
bool	mv_check_collusion(int new_x, int new_y, char **map, char comp);
// object
t_player	*init_player(t_game *game, mlx_image_t *img ,t_point pos);
void	obj_update_mvdirection(t_game *game, double rotation);

// utils
t_mapscan	*readmap(char *mapfile);
bool	load_resources(t_game *game);

void	board_clean(mlx_image_t *drawing_board);

void	cast_rays(t_game *game);

double normalizeAngle(double angle);

#endif
