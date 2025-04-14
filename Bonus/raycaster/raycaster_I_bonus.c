# include "../include/raycaster_bonus.h"

int	check_wall(t_game *game, t_vector2 *hitp, char **map, t_point map_size)
{
    int x_tile;
    int y_tile;

    x_tile = (hitp->x / TILE_SIZE);
    y_tile = (hitp->y / TILE_SIZE);
    if (isinf(hitp->y)|| isinf(hitp->x))
        hitp->y = -1;
    else if ((int)hitp->y < 0 || (int)hitp->x < 0)
        hitp->y = -1;
    else if (y_tile >= map_size.y || x_tile >= map_size.x)
        hitp->y = -1;
    else if (map[y_tile][x_tile] == 0)
        hitp->y = -1;
    if (hitp->y == -1 || map[y_tile][x_tile] == '1')
		return (0);
    if (game->door.door_ray.hitp.x == -1 && map[y_tile][x_tile] == 'D')
    {
        game->door.door_ray.hitp.x = hitp->x;
        game->door.door_ray.hitp.y = hitp->y;
    }
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
    t_door door;

    map = game->mapscan->map;
    map_size = game->mapscan->mapsize;
    while (check_wall(game, hit, map, map_size))
    {
        hit->x = hit->x + Xa;
        hit->y = hit->y + Ya;
    }
}

t_vector2 horizontal_intersection(t_game *game, double ray_angle, int *v_d)
{
    t_data data;
    
    data.hit = (t_vector2){0};
    game->door.door_ray.hitp = (t_vector2){-1};
    data.player = game->player;
    if (v_d[0] == looking_up)
    {
        data.py = floor(data.player->position.y / TILE_SIZE) * TILE_SIZE - next_tile;
        data.ya = -TILE_SIZE;
    }
    else
    {
        data.py = floor(data.player->position.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE + next_tile;
        data.ya = TILE_SIZE;
    }
    data.xa = fabs(data.ya / tan(ray_angle));
    if (v_d[1] == looking_right)
        data.px = data.player->position.x + fabs((data.py - data.player->position.y) / tan(ray_angle))  - next_tile;
    else
    {
        data.px = data.player->position.x - fabs((data.py - data.player->position.y) / tan(ray_angle)) + next_tile;
        data.xa *= -1;
    }   
    data.hit.x = data.px;
    data.hit.y = data.py;
    find_wall_hit(game, &data.hit, data.xa, data.ya);
    return data.hit;
}

t_vector2 vertical_intersection(t_game *game, double ray_angle, int *v_d)
{
    t_data data;
    
    data.hit = (t_vector2){0};
    game->door.door_ray.hitp = (t_vector2){-1};
    data.player = game->player;
    if (v_d[1] == looking_right)
    {
        data.px = floor(data.player->position.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE + next_tile;
        data.xa = TILE_SIZE;
    }
    else
    {
        data.px = floor(data.player->position.x / TILE_SIZE) * TILE_SIZE - next_tile;
        data.xa = -TILE_SIZE;
    }
    
    data.ya = fabs(data.xa * tan(ray_angle));
    if (v_d[0] == looking_down)
        data.py = data.player->position.y + fabs((data.player->position.x - data.px) * tan(ray_angle)) - next_tile;
    else
    {
        data.py = data.player->position.y - fabs((data.player->position.x - data.px) * tan(ray_angle)) + next_tile;
        data.ya *= -1;
    }
    data.hit.x = data.px;
    data.hit.y = data.py;
    find_wall_hit(game, &data.hit, data.xa, data.ya);
    return data.hit;
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

t_ray_dat find_nearest_hit(t_game *game, double ray_angle)
{
    t_vector2 h_hit[2];
    t_vector2 v_hit[2];
    t_player    *player;
    int v_d[2];
    double h_dist;
    double v_dist;

    player = game->player;
    vision_derction(ray_angle, v_d);
    h_hit[0] = horizontal_intersection(game, ray_angle, v_d);
    h_hit[1] = game->door.door_ray.hitp;
    v_hit[0] = vertical_intersection(game, ray_angle, v_d);
    v_hit[1] = game->door.door_ray.hitp;
    
    h_dist = sqrt(powf(player->position.x - h_hit[0].x, 2) + 
    powf(player->position.y - h_hit[0].y, 2));
    v_dist = sqrt(powf(player->position.x - v_hit[0].x, 2) + 
    powf(player->position.y - v_hit[0].y, 2));

    double h_door_dist = sqrt(powf(player->position.x - h_hit[1].x, 2) +
    powf(player->position.y - h_hit[1].y, 2));
    double v_door_dist = sqrt(powf(player->position.x - v_hit[1].x, 2) +
    powf(player->position.y - v_hit[1].y, 2));
    if (h_hit[1].x != -1 && (v_hit[1].x == -1 || h_door_dist < v_door_dist))
    {
        game->door.door_ray.hitp = h_hit[1];
        game->door.door_ray.ver_hor = 'H';
    }
    else if (v_hit[1].x != -1 && (h_hit[1].x == -1 || v_door_dist < h_door_dist))
    {
        game->door.door_ray.hitp = v_hit[1];
        game->door.door_ray.ver_hor = 'V';
    }
   
    if (v_hit[0].y != -1 && (h_hit[0].y == -1 || h_dist > v_dist))
        return (get_ray_data(v_hit[0], v_d, 'V'));
    return (get_ray_data(h_hit[0], v_d, 'H'));
}

void	cast_rays(t_game *game)
{
	double	rotate_angle;
	double	ray_angle;
	double 	angle_shift;
	int x;

	x = 0;
	ray_angle = radians(-30);
	angle_shift = ((double)radians(60) / WIDTH );
    board_clean(game->world->door_img);
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