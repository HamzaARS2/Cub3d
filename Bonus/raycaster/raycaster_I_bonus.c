# include "../include/raycaster_bonus.h"
# include <math.h>
#define next_tile 1.0E-8

int	check_wall(t_vector2 *hitp, char **map, t_point map_size)
{
    int x_tile;
    int y_tile;

    x_tile = (hitp->x / TILE_SIZE);
    y_tile = (hitp->y / TILE_SIZE);
    //printf("py: %f y: %d and px: %f x: %d\n", hitp->y, y_tile, hitp->x, x_tile);
    if (isinf(hitp->y)|| isinf(hitp->x))
        hitp->y = -1;
    else if (hitp->y > HEIGHT || hitp->x > WIDTH)
        hitp->y = -1;
    else if (hitp->y < 0 || hitp->x < 0)
        hitp->y = -1;
    else if (y_tile >= map_size.y || x_tile >= map_size.x)
        hitp->y = -1;
    else if (map[y_tile][x_tile] == 0)
        hitp->y = -1;
    if (hitp->y == -1 || map[y_tile][x_tile] == '1')
		return (0);
	return (1);
}

void	vision_derction(double angel, int *v_d)
{
	if (angel > M_PI)
		v_d[0] = looking_up;
	else
		v_d[0] = looking_down;
	if (angel > M_PI_2 && angel < 1.5 * M_PI)
		v_d[1] = looking_left;
	else
		v_d[1] = looking_right;
}

void    find_wall_hit(t_game *game, t_vector2 *hit, double Xa, double Ya)
{
    char **map;
    t_point map_size;

    map = game->mapscan->map;
    map_size = game->mapscan->mapsize;
    while (check_wall(hit, map, map_size))
    {
        hit->x = hit->x + Xa;
        hit->y = hit->y + Ya;
    }
}

t_vector2 horizontal_intersection(t_game *game, float ray_angle, int *v_d)
{
    t_vector2 hit;
    t_player *player;
    double Ax;
    double Ay;
    double Xa;
    double Ya;
    
    hit.x = 0;
    hit.y = 0;
    player = game->player;
    if (v_d[0] == looking_up)
    {
        Ay = floor(player->position.y / TILE_SIZE) * TILE_SIZE - next_tile;
        Ya = -TILE_SIZE;
    }
    else
    {
        Ay = floor(player->position.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE + next_tile;
        Ya = TILE_SIZE;
    }
    Xa = fabs(Ya / tan(ray_angle));
    if (v_d[1] == looking_right)
        Ax = player->position.x + fabs((Ay - player->position.y) / tan(ray_angle))  - next_tile;
    else
    {
        Ax = player->position.x - fabs((Ay - player->position.y) / tan(ray_angle)) + next_tile;
        Xa *= -1;
    }   
    hit.x = Ax;
    hit.y = Ay;
    find_wall_hit(game, &hit, Xa, Ya);
    return hit;
}

t_vector2 vertical_intersection(t_game *game, float ray_angle, int *v_d)
{
    t_vector2 hit;
    t_player *player;
    double Bx;
    double By;
    double Xa;
    double Ya;
    
    hit.x = 0;
    hit.y = 0;
    player = game->player;
    if (v_d[1] == looking_right)
    {
        Bx = floor(player->position.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE + next_tile;
        Xa = TILE_SIZE;
    }
    else
    {
        Bx = floor(player->position.x / TILE_SIZE) * TILE_SIZE - next_tile;
        Xa = -TILE_SIZE;
    }
    
    Ya = fabs(Xa * tan(ray_angle));
    if (v_d[0] == looking_down)
        By = player->position.y + fabs((player->position.x - Bx) * tan(ray_angle)) - next_tile;
    else
    {
        By = player->position.y - fabs((player->position.x - Bx) * tan(ray_angle)) + next_tile;
        Ya *= -1;
    }
    hit.x = Bx;
    hit.y = By;
    find_wall_hit(game, &hit, Xa, Ya);
    return hit;
}

t_ray_dat get_ray_data(t_vector2 hit, int *v_d, char c)
{
    t_ray_dat ray_dat;

    ray_dat.hitp = hit;
    if (c == 'V' )
    {
        ray_dat.ver_hor = c;
        if (v_d[1] == looking_left)
            ray_dat.direction = 'W';
        else
            ray_dat.direction = 'E';
    }
    else if (c == 'H')
    {
        ray_dat.ver_hor = c;
        if (v_d[0] == looking_up)
            ray_dat.direction = 'N';
        else
            ray_dat.direction = 'S';
    }
    return (ray_dat);
}

t_ray_dat find_nearest_hit(t_game *game, float ray_angle)
{
    t_vector2 h_hit;
    t_vector2 v_hit;
    t_player    *player;
    int v_d[2];
    double h_dist;
    double v_dist;
    t_ray_dat ray_data;

    player = game->player;
    vision_derction(ray_angle, v_d);
    h_hit = horizontal_intersection(game, ray_angle, v_d);
    v_hit = vertical_intersection(game, ray_angle, v_d);
    
    h_dist = sqrt(powf(player->position.x - h_hit.x, 2) + 
    powf(player->position.y - h_hit.y, 2));
    v_dist = sqrt(powf(player->position.x - v_hit.x, 2) + 
    powf(player->position.y - v_hit.y, 2));
    if (v_hit.y != -1 && (h_hit.y == -1 || h_dist > v_dist))
        return (get_ray_data(v_hit, v_d, 'V'));
    return (get_ray_data(h_hit, v_d, 'H'));
}

void	cast_rays(t_game *game)
{
	double	rotate_angle;
	double	ray_angle;
	double 	angle_shift;
	int x;

	// printf("x: %f, y: %f\n", game->player->position.x, game->player->position.y);
	x = 0;
	ray_angle = RADIANS(-30);
	angle_shift = ((double)RADIANS(60) / WIDTH );
	// printf("ang: %f, angle_sh: %f\n", game->player->direction.rotatin_angle, angle_shift);
	board_clean(game->world->drawing_board);
	rotate_angle = game->player->direction.rotatin_angle;
	game->player->direction.rotatin_angle = normalizeAngle(game->player->direction.rotatin_angle + ray_angle);

    // printf("angle SHIFT value: %f\n", ray_angle);
    while (ray_angle < RADIANS(30)&& x < WIDTH)
	{
		// printf("/////cast angle : %f\n", game->player->direction.rotatin_angle);
		bresenham_line(game, &x, ray_angle);
		game->player->direction.rotatin_angle = normalizeAngle(game->player->direction.rotatin_angle +  angle_shift);
		ray_angle += angle_shift;
		x++;
        //printf("angle SHIFT value: %f\n", ray_angle);
	}
	game->player->direction.rotatin_angle = rotate_angle;
	// printf("ang: %f\n", game->player->direction.rotatin_angle);
}
//0.523599