# include "../include/raycaster_bonus.h"

void draw_wall(t_game *game, double distance, double angle, int x);

double  radians(double angle)
{
	return (angle * (M_PI / 180));
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

void	send_ray(t_game *game, int x, double angle)
{
    t_player    *player;
	t_vector2 	hit;
	t_ray_dat	ray_dat;

    player = game->player;
	ray_dat = find_nearest_hit(game, game->player->direction.rotatin_angle);
	hit = ray_dat.hitp;
	ray_dat.current_column = x;
	ray_dat.distance = (sqrt(powf(player->position.x - hit.x, 2) + 
    powf(player->position.y - hit.y, 2)) * cos(angle));
	game->door.door_ray.distance = (sqrt(powf(player->position.x - game->door.door_ray.hitp.x, 2) + 
	powf(player->position.y - game->door.door_ray.hitp.y, 2)) * cos(angle));
	if (ray_dat.distance < game->door.door_ray.distance)
		game->door.door_ray.hitp.x = -1.0;
	if (game->door.door_ray.hitp.x != -1.0)
		draw_wall(game, game->door.door_ray.distance, angle, x);
	wd_render_walls(game->world, ray_dat);
}


void draw_wall(t_game *game, double distance, double angle, int x)
{
	 double focal;
	 double wall_h;
	 double start;
	 int 	pixel_offset;

	if (game->door.closed || (game->door.open && mv_check_collusion(
		game->player->position.x, game->player->position.y, game->mapscan->map, 'D')))
	{
		//DELET this code and replace it with door texture function.
		////////////////////////////////////////////
		focal = (double) (WIDTH / 2) / tan(radians((FOV / 2)));
		distance *= cos(angle);
		wall_h = (32 / distance) * focal;
		game->door.closed =true;
		start = (HEIGHT / 2) - (wall_h / 2);
		if (start < 0)
			start = 0;
		pixel_offset = (wall_h - HEIGHT) / 2;
		if (pixel_offset < 0)
			pixel_offset = 0;

		while(pixel_offset < wall_h && start < HEIGHT)
		{
			mlx_put_pixel(game->world->door_img, x, 
				start, get_rgba(51,175,255,255));
			pixel_offset++;
			start++;
		}
		///////////////////////////////////
	}
	else if (!game->door.closed && game->door.door_ray.distance > TILE_SIZE *5 
		&& mv_check_collusion(game->player->position.x, game->player->position.y,
			 game->mapscan->map, 'D'))
		game->door.closed = true;
	else if (!game->door.closed)
	{
		game->door.open = false;
	 	return;
	}

}
