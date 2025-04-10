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
# include <math.h>

typedef enum e_direction {
		looking_up,
		looking_down,
		looking_right,
		looking_left,
} t_direction;

# define RADIANS(d) (d * (M_PI / 180))
# define FOV 60
# define RES 4
# define NUM_RAYS (WIDTH / RES)



typedef struct s_data
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
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

void	set_direction(t_draw *mat, t_data *data);
double	normalizeAngle(double angle);
t_ray_dat find_nearest_hit(t_game *game, double ray_angle);
void	drawing_loop(mlx_image_t *image, t_data *data, t_draw mat, char **map);
#endif