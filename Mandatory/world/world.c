/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:15:50 by helarras          #+#    #+#             */
/*   Updated: 2025/03/08 21:41:08 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"
#include "../include/world.h"
#include "../include/raycaster.h"

t_world	*init_world(mlx_t *mlx, t_colors colors)
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

void	wd_load_textures(t_world *world, t_texpath texpaths)
{
	world->textures.north_texture.img = gfx_create_teximage(world->mlx, world->graphics, texpaths.north_tex);
	world->textures.east_texture.img = gfx_create_teximage(world->mlx, world->graphics, texpaths.east_tex);
	world->textures.south_texture.img = gfx_create_teximage(world->mlx, world->graphics, texpaths.south_tex);
	world->textures.west_texture.img = gfx_create_teximage(world->mlx, world->graphics, texpaths.west_tex);
}

void	wd_prepare_colors(t_world *world)
{
	world->textures.north_texture.pixels= wd_get_color_buffer(world->textures.north_texture.img);
	world->textures.east_texture.pixels = wd_get_color_buffer(world->textures.east_texture.img);
	world->textures.south_texture.pixels = wd_get_color_buffer(world->textures.south_texture.img);
	world->textures.west_texture.pixels = wd_get_color_buffer(world->textures.west_texture.img);
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
	float scale_factor;
	t_render_info info;
	t_wd_texture texture;

	texture = wd_texture_bydirection(world, rays_info.direction);
	info = wd_calc_render_info(rays_info, texture);
	scale_factor = ((float)texture.img->height / info.wall_strip_height);
	y = info.wall_top_pixel;
	while (y < info.wall_bot_pixel - 1)
	{
		info.tex_offset_y = (info.pixel_offset++) * scale_factor;
		color = texture.pixels[info.tex_offset_y][info.tex_offset_x];
		mlx_put_pixel(world->drawing_board, rays_info.current_column, y++, color);
	}
}

/*
texture size = 32 | wall height = 128
0
0
0
0
1
*/