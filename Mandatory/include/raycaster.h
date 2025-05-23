/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:33:54 by nhimad            #+#    #+#             */
/*   Updated: 2025/04/19 11:40:19 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "game.h"
# include "world.h"
# include <math.h>

# define NEXT_T 1.0E-8
# define INVALID_DATA -1
# define FOV 60

typedef enum e_direction
{
	looking_up,
	looking_down,
	looking_right,
	looking_left,
}				t_direction;

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

double			normalize_angle(double angle);
t_ray_dat		find_nearest_hit(t_game *game, double ray_angle);
void			vision_dierction(double angel, int *v_d);
t_ray_dat		get_ray_data(t_vector2 hit, int *v_d, char c);
void			find_wall_hit(t_game *game, t_vector2 *hit, double Xa,
					double Ya);
void			render_doors(t_game *game, double distance, double angle,
					int x);
double			get_distance(t_vector2 hit, t_player *player);
void			get_hori_y(t_data *data, int *v_d);
void			geth_hori_x(t_data *data, double ray_angle, int *v_d);
t_vector2		horizontal_intersection(t_game *game, double ray_angle,
					int *v_d);
void			get_vert_x(t_data *data, int *v_d);
void			get_vert_y(t_data *data, double ray_angle, int *v_d);
int				check_wall(t_vector2 *hitp, char **map, t_point map_size);
#endif