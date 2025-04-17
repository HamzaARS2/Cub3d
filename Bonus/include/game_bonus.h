/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:09:35 by helarras          #+#    #+#             */
/*   Updated: 2025/04/17 19:03:41 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_BONUS_H
# define GAME_BONUS_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "animator_bonus.h"
# include "gfx_manager_bonus.h"
# include "mapscan_bonus.h"
# include "world_bonus.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1400
# define HEIGHT 900

# define MAP_WIDTH 300
# define MAP_HEIGHT 250

# define ROTATION_SPEED 2

typedef struct s_Dvector
{
	char		walk_direction;
	double		rotatin_angle;
}				t_Dvector;

typedef struct s_player
{
	mlx_image_t	*image;
	t_vector2	position;
	t_Dvector	direction;
	double		speed;
}				t_player;

typedef struct s_door
{
	t_ray_dat	door_ray;
	double		disp_ratio;
	bool		closed;
	bool		open;
}				t_door;

typedef struct s_game
{
	t_mapscan	*mapscan;
	t_world		*world;
	mlx_t		*mlx;
	t_player	*player;
	t_door		door;
	t_point		mouse_pos;
	mlx_image_t	*map_img;
	t_animator	*animator;
}				t_game;

void			send_ray(t_game *game, int x, double angle);

bool			init_game(t_game *game, char *mapfile);
void			init_angle(t_game *game);
void			run_game(t_game *game);
void			update(void *param);
void			cleanup_game(t_game game);

// renderer
bool			draw_player(t_game *game);
void			draw_minimap(t_game *game);
// movements
void			mv_move_player(t_player *object, double new_x, double new_y);
void			mv_handle_moves(t_game *game);
bool			mv_check_collusion(int new_x, int new_y, char **map, char c);
bool			check_door_collusion(int new_x, int new_y, char **map,
					t_game *game);
// object
t_player		*init_player(t_game *game, mlx_image_t *img, t_point pos);
void			obj_update_mvdirection(t_game *game, double rotation,
					t_Dvector direction);

// utils
bool			check_door_collusion(int new_x, int new_y, char **map,
					t_game *game);
t_mapscan		*readmap(char *mapfile);
bool			load_resources(t_game *game);
void			board_clean(mlx_image_t *drawing_board);
void			cast_rays(t_game *game);
double			radians(double angle);
double			normalize_angle(double angle);

#endif
