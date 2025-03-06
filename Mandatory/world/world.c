/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:15:50 by helarras          #+#    #+#             */
/*   Updated: 2025/03/06 21:51:49 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"
#include "../include/world.h"
#include "../include/raycaster.h"

t_world	*init_world(mlx_t *mlx, mlx_image_t *drawing_board, t_colors colors)
{
	t_world *world;

	world = malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	world->mlx = mlx;
	world->graphics = NULL;
	world->colors = colors;
	world->cf_img = gfx_create_image(mlx, world->graphics, WIDTH, HEIGHT);
	world->drawing_board = 	gfx_create_image(mlx, world->graphics, WIDTH, HEIGHT);
	return (world);
}

uint32_t **convert_to_uint32_array(uint8_t *pixels, int width, int height) {
	int i;
	i = 0;
    if (!pixels)
        return NULL;

    uint32_t **array = malloc(height * sizeof(uint32_t *));
    if (!array)
        return NULL;

    for (int y = 0; y < height; y++) {
        array[y] = malloc(width * sizeof(uint32_t));
        if (!array[y]) {
            while (y-- > 0) free(array[y]);
            free(array);
            return NULL;
        }
        for (int x = 0; x < width; x++) {
            array[y][x] = get_rgba(pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
			i += 4;
        }
    }
    return array;
}

void initialize_texture_arrays(t_textures *textures, int width, int height) {
    textures->north_pixels = convert_to_uint32_array(textures->north_texture->pixels, width, height);
    textures->south_pixels = convert_to_uint32_array(textures->south_texture->pixels, width, height);
    textures->east_pixels = convert_to_uint32_array(textures->east_texture->pixels, width, height);
    textures->west_pixels = convert_to_uint32_array(textures->west_texture->pixels, width, height);
}


void	wd_load_textures(t_world *world, t_texpath texpaths)
{
	world->textures.north_texture = gfx_create_teximage(world->mlx, world->graphics, texpaths.north_tex);
	world->textures.east_texture = gfx_create_teximage(world->mlx, world->graphics, texpaths.east_tex);
	world->textures.south_texture = gfx_create_teximage(world->mlx, world->graphics, texpaths.south_tex);
	world->textures.west_texture = gfx_create_teximage(world->mlx, world->graphics, texpaths.west_tex);
	initialize_texture_arrays(&world->textures, 32, 32);
}

void	wd_render_cf(t_world *world)
{
	t_point start;
	t_point end;

	// drawing the ceiling
	start = (t_point) {0};
	end = (t_point) {WIDTH, HEIGHT / 2};
	gfx_draw_rect(world->cf_img, start, end, world->colors.ccolor);
	// drawing the floor
	start = (t_point) {0, HEIGHT / 2};
	end = (t_point) {WIDTH, HEIGHT};
	gfx_draw_rect(world->cf_img, start, end, world->colors.fcolor);
}

void	wd_render_walls(t_world *world, t_ray_dat rays_info)
{
	int y;
	int color;
	t_render_info info;
	mlx_image_t *texture;
	texture = wd_texture_bydirection(world, rays_info.direction);
	info = wd_calc_render_info(rays_info);
	float temp = ((float)TEXTURES_SIZE / info.wall_strip_height);
	y = info.wall_top_pixel;
	while (y < info.wall_bot_pixel - 1)
	{
		info.tex_offset_y = (y - info.wall_top_pixel) * temp;
		color = wd_get_texture_color(world, texture, info.tex_offset_x, info.tex_offset_y);
		// color = get_rgba(0,255,0,255);
		mlx_put_pixel(world->drawing_board, rays_info.current_column, y++, color);
	}
}