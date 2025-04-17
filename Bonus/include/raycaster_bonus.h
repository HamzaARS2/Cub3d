/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:20:51 by nhimad            #+#    #+#             */
/*   Updated: 2025/04/17 19:02:37 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_BONUS_H
# define RAYCASTER_BONUS_H

# include "game_bonus.h"
# include "world_bonus.h"
# include <math.h>

# define NEXT_T 1.0E-8
# define INVALID_DATA -1

typedef enum e_direction
{
	looking_up,
	looking_down,
	looking_right,
	looking_left,
}				t_direction;

# define FOV 60

typedef struct s_data
{
	t_vector2	hit;
	t_player	*player;
	double		px;
	double		py;
	double		xa;
	double		ya;
}				t_data;

typedef struct s_draw
{
	int			move_x;
	int			move_y;
	int			dx;
	int			dy;
	int			err;
	int			temp;
}				t_draw;

double			radians(double angle);
double			normalize_angle(double angle);
t_ray_dat		find_nearest_hit(t_game *game, double ray_angle);
void			vision_dierction(double angel, int *v_d);
t_ray_dat		get_ray_data(t_vector2 hit, int *v_d, char c);
void			find_wall_hit(t_game *game, t_vector2 *hit, double Xa,
					double Ya);
void			render_doors(t_game *game, double distance, double angle,
					int x);
double			get_distance(t_vector2 hit, t_player *player);
void			get_hori_y(t_data *data, double ray_angle, int *v_d);
void			geth_hori_x(t_data *data, double ray_angle, int *v_d);
t_vector2		horizontal_intersection(t_game *game, double ray_angle,
					int *v_d);
void			get_vert_x(t_data *data, double ray_angle, int *v_d);
void			get_vert_y(t_data *data, double ray_angle, int *v_d);
#endif