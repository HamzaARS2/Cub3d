/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:20:51 by nhimad            #+#    #+#             */
/*   Updated: 2025/03/06 13:55:07 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "game_bonus.h"
# include "world_bonus.h"
# include <math.h>

#define next_tile 1.0E-8

typedef enum e_direction {
		looking_up,
		looking_down,
		looking_right,
		looking_left,
} t_direction;

# define FOV 60




typedef struct s_data
{
	t_vector2 hit;
    t_player *player;
    double px;
    double py;
    double xa;
    double ya;
}		t_data;

typedef struct s_draw
{
	int	move_x;
	int	move_y;
	int	dx;
	int	dy;
	int	err;
	int	temp;
}		t_draw;

double	radians(double angle);
double	normalizeAngle(double angle);
t_ray_dat find_nearest_hit(t_game *game, double ray_angle);
#endif