# include "../include/raycaster_bonus.h"
# include "../include/world_bonus.h"

void draw_wall(t_game *game, double distance, double angle, int *x);

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
	double two_pi;

	two_pi = 2 * M_PI;
	while (angle < 0)
		angle += two_pi;
	while (angle >= two_pi)
		angle -= two_pi;
	return (angle);
}

void	bresenham_line(t_game *game, int x, double angle)
{
    t_player    *player;
	t_vector2 	hit;
	t_ray_dat	ray_dat; //here we store hit poit cordination, and direction

    player = game->player;
	ray_dat = find_nearest_hit(game, game->player->direction.rotatin_angle);
	hit = ray_dat.hitp;
	ray_dat.current_column = x;
	ray_dat.distance = (sqrt(powf(player->position.x - hit.x, 2) + 
    powf(player->position.y - hit.y, 2)) * cos(angle));

	game->door.door_ray.distance = (sqrt(powf(player->position.x - game->door.door_ray.hitp.x, 2) + 
	powf(player->position.y - game->door.door_ray.hitp.y, 2)) * cos(angle));

	//here i draw the door, notice there is a door struct in game struct, so you work with it.
	if (game->door.door_ray.hitp.x != -1)
		draw_wall(game, game->door.door_ray.distance, angle, x);

	wd_render_walls(game->world, ray_dat);
}

void draw_wall(t_game *game, double distance, double angle, int x)
{
	 double focal;
	 double wall_h;
	 double start;
	 int 	pixel_offset;

	 focal = (double) (WIDTH / 2) / tan(RADIANS((FOV / 2)));
	 distance *= cos(angle);
	 wall_h = (25 / distance) * focal;
	 start = (HEIGHT / 2) - (wall_h / 2);
	 if (start < 0)
	 	start = 0;
	pixel_offset = (wall_h - HEIGHT) / 2;
	if (pixel_offset < 0)
		pixel_offset = 0;
	while( pixel_offset < wall_h && start < HEIGHT - 1)
	{
		mlx_put_pixel(game->world->door_img, x, 
			start, get_rgba(51,175,255,255));
		pixel_offset++;
		start++;
	}
}
