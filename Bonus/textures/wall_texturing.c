
#include "../include/game_bonus.h"
#include "../include/raycaster_bonus.h"


void    load_textures(t_game *game)
{
    t_texpath texpaths;

    texpaths = game->mapscan->texpaths;
    game->textures.north_texture = gfx_create_teximage(game, texpaths.north_tex);
    game->textures.south_texture = gfx_create_teximage(game, texpaths.south_tex);
    game->textures.east_texture = gfx_create_teximage(game, texpaths.east_tex);
    game->textures.west_texture = gfx_create_teximage(game, texpaths.west_tex);
}

int	get_texture_color(t_game *game, int tex_offset_x, int tex_offset_y) {
	mlx_image_t * tex = game->textures.north_texture;
	int texel_color = ((tex->width * tex_offset_y) + tex_offset_x) * 4;
    // if (texel_color >= tex->width * tex->height)
    //     return get_rgba(255,0,0,255);
    int r = tex->pixels[texel_color];
    // while(1);
	int g = tex->pixels[texel_color+1];
	int b = tex->pixels[texel_color+2];
	int a = tex->pixels[texel_color+3];
	return get_rgba(r,g,b,a);
}

void    render_wall_texture(t_game *game, double distance, double angle, int x, t_vector2 hit) {
    double wall_strip_height;
    int projection;
    int y;
    int pixel_offset;
    int tex_offset_x;
    int tex_offset_y;
    int wall_top_pixel;
    int wall_bot_pixel;
    distance *= cos(RADIANS(angle));
    projection = (WIDTH / 2) / tan(RADIANS(FOV / 2));
    wall_strip_height = (TILE_SIZE / distance) * projection;
    wall_top_pixel = (HEIGHT / 2) - (wall_strip_height / 2);
    wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;

    wall_bot_pixel = (HEIGHT / 2) + (wall_strip_height / 2);
    wall_bot_pixel = wall_bot_pixel > HEIGHT ? HEIGHT : wall_bot_pixel;

    if (game->is_vertical_hit)
        tex_offset_x = (int)hit.y % TILE_SIZE;
    else
        tex_offset_x = (int)hit.x % TILE_SIZE;
    y = wall_top_pixel;
    while (y < wall_bot_pixel)
    {
        int dft = y + (wall_strip_height / 2) - (HEIGHT / 2);
        tex_offset_y = ((y - wall_top_pixel) * ((float)game->textures.north_texture->height / wall_strip_height));
        int color = get_texture_color(game, tex_offset_x, tex_offset_y);
        mlx_put_pixel(game->drawing_board, x, y, color);
        y++;
    }
}