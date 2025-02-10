# include "../include/raycaster.h"

int check_if_wall(char **map, int x, int y)
{
	if (y / TILE_SIZE > 30 || x / TILE_SIZE > 15)
		return (printf("??y= %d ==>y_p %d||x= %d===> x_p %d\n\n", y,  y / TILE_SIZE, x,  x / TILE_SIZE), 1);		
	
	return (map[y / TILE_SIZE][x / TILE_SIZE] == '1');
}

void	set_direction(t_draw *mat, t_data *data)
{
	if (data->x1 < data->x2)
		mat->move_x = 1;
	else
		mat->move_x = -1;
	if (data->y1 < data->y2)
		mat->move_y = 1;
	else
		mat->move_y = -1;
	if (mat->dx > mat->dy)
		mat->err = mat->dx / 2;
	else
		mat->err = -mat->dy / 2;
}

void	board_clean(mlx_image_t *drawing_board)
{
	unsigned int	color;
	int x;
	int y;

	y = -1;
	x = -1;
	color = 0x00000000;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
			mlx_put_pixel(drawing_board, x, y, color);
	}
}

void	drawing_loop(mlx_image_t *image, t_data *data, t_draw mat, char **map)
{
	unsigned int	color;

    color = 0x6A5ACDFF;
	
	while (1)
	{
		mlx_put_pixel(image, data->x1, data->y1, color);
		if ((data->x1 == data->x2 && data->y1 == data->y2))
			break ;
		mat.temp = mat.err;
		if (mat.temp > -mat.dx)
		{
			mat.err -= mat.dy;
			data->x1 += mat.move_x;
		}
		if (mat.temp < mat.dy)
		{
			mat.err += mat.dx;
			data->y1 += mat.move_y;
		}
	}
}


double normalizeAngle(double angle) 
{
	double n_angle;

    n_angle = fmod(angle, 2 * M_PI);
    if (n_angle <= 0)
        n_angle += 2 * M_PI;
	return (n_angle);
}

void	bresenham_line(t_game *game)
{
	t_draw		mat;
    t_object    *player;
    t_data      data;
	t_vector3 	hit;

    mat = (t_draw) {0};
    player = game->player;
    data.x1 = player->position.x + OBJ_SIZE / 2;
    data.y1 = player->position.y + OBJ_SIZE / 2;
	hit = find_nearest_hit(game, game->player->direction.rotatin_angle);
    data.x2 = hit.x;
    data.y2 = hit.y;
	printf("x: %d ==> %f ## y: %d ==> %f\n", data.x2, hit.x, data.y2, hit.y);
	mat.dx = fabs((float)data.x2 - data.x1);
	mat.dy = fabs((float)data.y2 - data.y1); 
	set_direction(&mat, &data);
	drawing_loop(game->drawing_board, &data, mat, game->mapscan->map);
}
