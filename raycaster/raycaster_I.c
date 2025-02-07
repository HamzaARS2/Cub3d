# include "../include/raycaster.h"

t_vector3 horizontal_intersection(t_game *game, float ray_angle)
{
    t_vector3 hit;
    t_object *player;
    float Ax;
    float Ay;
    float Xa;
    float Ya;
    
    hit.x = 0;
    hit.y = 0;
    player = game->player;
    if (ray_angle > M_PI)
    {
        Ay = floor(player->position.y / TILE_SIZE) * TILE_SIZE - 1;
        Ya = -TILE_SIZE;
    }
    else
    {
        Ay = floor(player->position.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
        Ya = TILE_SIZE;
    }
    
    Ax = (Ay - player->position.y) / tan(ray_angle) + player->position.x;
    Xa = Ya / tan(ray_angle);
    
    hit.x = Ax;
    hit.y = Ay;
    
    return hit;
}

t_vector3 vertical_intersection(t_game *game, float ray_angle)
{
    t_vector3 hit;
    t_object *player;
    float Bx;
    float By;
    float Xa;
    float Ya;
    
    hit.x = 0;
    hit.y = 0;
    player = game->player;
    if (ray_angle < M_PI/2 || ray_angle > 3*M_PI/2)
    {
        Bx = floor(player->position.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
        Xa = TILE_SIZE;
    }
    else
    {
        Bx = floor(player->position.x / TILE_SIZE) * TILE_SIZE - 1;
        Xa = -TILE_SIZE;
    }
    
    By = player->position.y + (player->position.x - Bx) * tan(ray_angle);
    Ya = Xa * tan(ray_angle);
    
    hit.x = Bx;
    hit.y = By;
    
    return hit;
}

t_vector3 find_nearest_hit(t_game *game, float ray_angle)
{
    t_vector3 h_hit;
    t_vector3 v_hit;
    t_object    *player;
    float h_dist;
    float v_dist;

    player = game->player;
    h_hit = horizontal_intersection(game, ray_angle);
    v_hit = vertical_intersection(game, ray_angle);
    
    h_dist = sqrtf(powf(h_hit.x - player->position.x, 2) + 
                   powf(h_hit.y - player->position.y, 2));
    v_dist = sqrtf(powf(v_hit.x - player->position.x, 2) + 
                   powf(v_hit.y - player->position.y, 2));
    
    if (h_dist < v_dist)
        return h_hit;
    return v_hit;
}
