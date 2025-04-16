# include "../include/raycaster.h"

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
	ray_dat.distance = get_distance(hit, player) * cos(angle);
	wd_render_walls(game->world, ray_dat);
}

void	cast_rays(t_game *game)
{
	double	rotate_angle;
	double	ray_angle;
	double 	angle_shift;
	int x;

	x = 0;
	ray_angle = radians((FOV / 2)*-1);
	angle_shift = ((double)radians(FOV) / WIDTH );
	board_clean(game->world->drawing_board);
	rotate_angle = game->player->direction.rotatin_angle;
	game->player->direction.rotatin_angle = normalizeAngle(game->player->direction.rotatin_angle
     + ray_angle);

    while (ray_angle < radians(30)&& x < WIDTH)
	{
		send_ray(game, x, ray_angle);
		game->player->direction.rotatin_angle = normalizeAngle(game->player->direction.rotatin_angle
         +  angle_shift);
		ray_angle += angle_shift;
		x++;
	}
	game->player->direction.rotatin_angle = rotate_angle;
}
