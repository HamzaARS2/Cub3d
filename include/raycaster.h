#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "game.h"
#include "mapscan.h"
#include <math.h>

#define FOV  (60 * ( M_PI/ 180))
#define RES 4
#define NUM_RAYS (WIDTH / RES)

typedef struct s_data
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
}					t_data;

typedef struct s_draw
{
	int				move_x;
	int				move_y;
	int				dx;
	int				dy;
	int				err;
	int				temp;
}					t_draw;

int 	check_if_wall(char **map, int x, int y);
void	set_direction(t_draw *mat, t_data *data);
void	drawing_loop(mlx_image_t *image, t_data *data, t_draw mat, char **map);
#endif