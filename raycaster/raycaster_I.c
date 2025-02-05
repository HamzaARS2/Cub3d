# include "../include/raycaster.h"


typedef struct {
    t_vector3 pos;
    float angle;
} Player;

t_vector3 horizontal_intersection(Player player, float ray_angle)
{
    t_vector3 hit;
    float Ax;
    float Ay;
    float Xa;
    float Ya;
    
    hit.x = 0;
    hit.y = 0;
    
    if (ray_angle > M_PI)
    {
        Ay = floor(player.pos.y / TILE_SIZE) * TILE_SIZE - 1;
        Ya = -TILE_SIZE;
    }
    else
    {
        Ay = floor(player.pos.y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
        Ya = TILE_SIZE;
    }
    
    Ax = (Ay - player.pos.y) / tan(ray_angle) + player.pos.x;
    Xa = Ya / tan(ray_angle);
    
    hit.x = Ax;
    hit.y = Ay;
    
    return hit;
}

t_vector3 vertical_intersection(Player player, float ray_angle)
{
    t_vector3 hit;
    float Bx;
    float By;
    float Xa;
    float Ya;
    
    hit.x = 0;
    hit.y = 0;
    
    if (ray_angle < M_PI/2 || ray_angle > 3*M_PI/2)
    {
        Bx = floor(player.pos.x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
        Xa = TILE_SIZE;
    }
    else
    {
        Bx = floor(player.pos.x / TILE_SIZE) * TILE_SIZE - 1;
        Xa = -TILE_SIZE;
    }
    
    By = player.pos.y + (player.pos.x - Bx) * tan(ray_angle);
    Ya = Xa * tan(ray_angle);
    
    hit.x = Bx;
    hit.y = By;
    
    return hit;
}

t_vector3 find_nearest_hit(Player player, float ray_angle)
{
    t_vector3 h_hit;
    t_vector3 v_hit;
    t_vector3 final_hit;
    float h_dist;
    float v_dist;
    
    h_hit = horizontal_intersection(player, ray_angle);
    v_hit = vertical_intersection(player, ray_angle);
    
    h_dist = sqrtf(powf(h_hit.x - player.pos.x, 2) + 
                   powf(h_hit.y - player.pos.y, 2));
    v_dist = sqrtf(powf(v_hit.x - player.pos.x, 2) + 
                   powf(v_hit.y - player.pos.y, 2));
    
    if (h_dist < v_dist)
        final_hit = h_hit;
    else
        final_hit = v_hit;
    
    return final_hit;
}
