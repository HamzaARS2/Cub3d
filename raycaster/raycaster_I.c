# include "../include/raycaster.h"
#define next_tile 1.0E-8

int	check_wall(t_vector3 *hitp, char **map)
{
    printf("py: %f y: %d and px: %f x: %d\n", hitp->y, (int)hitp->y / TILE_SIZE, hitp->x, (int)hitp->x / TILE_SIZE);
	if (isinf(hitp->y )|| isinf(hitp->x )|| hitp->y < 0 || hitp->x < 0
		|| (int)(hitp->y / TILE_SIZE) > (15) || (int)(hitp->x
			/ TILE_SIZE) > (31))
		hitp->y = -1;
	if (hitp->y == -1 || map[(int)(hitp->y / TILE_SIZE)][(int)(hitp->x / TILE_SIZE)] == '1')
    {
        printf("HIT==> py: %f y: %d and px: %f x: %d\n", hitp->y, (int)hitp->y / TILE_SIZE, hitp->x, (int)hitp->x / TILE_SIZE);
		return (0);
	}
	return (1);
}

void	vision_derction(double angel, int *v_d)
{
	if (angel > 180)
		v_d[0] = looking_up;
	else
		v_d[0] = looking_down;
	if (angel > 90 && angel < 270)
		v_d[1] = looking_left;
	else
		v_d[1] = looking_right;
}

void    find_wall_hit(t_game *game, t_vector3 *hit, double Xa, double Ya)
{
    char **map;

    map = game->mapscan->map;
    while (check_wall(hit, map))
    {
        hit->x = hit->x + Xa;
        hit->y = hit->y + Ya;
    }
}

t_vector3 horizontal_intersection(t_game *game, float ray_angle, int *v_d)
{
    t_vector3 hit;
    t_object *player;
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

t_vector3 vertical_intersection(t_game *game, float ray_angle, int *v_d)
{
    t_vector3 hit;
    t_object *player;
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

t_vector3 find_nearest_hit(t_game *game, float ray_angle)
{
    t_vector3 h_hit;
    t_vector3 v_hit;
    t_object    *player;
    int v_d[2];
    double h_dist;
    double v_dist;

    player = game->player;
    vision_derction(ray_angle, v_d);
    ray_angle = RADIANS(ray_angle);
    h_hit = horizontal_intersection(game, ray_angle, v_d);
    v_hit = vertical_intersection(game, ray_angle, v_d);
    
    h_dist = sqrt(powf(player->position.x - h_hit.x, 2) + 
    powf(player->position.y - h_hit.y, 2));
    v_dist = sqrt(powf(player->position.x - v_hit.x, 2) + 
    powf(player->position.y - v_hit.y, 2));
    if (v_hit.y != -1 && (h_hit.y == -1 || h_dist > v_dist))
        return (v_hit);
    return (h_hit);
}

