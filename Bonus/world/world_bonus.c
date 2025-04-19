/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:15:50 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 13:02:48 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"
#include "../include/raycaster_bonus.h"
#include "../include/world_bonus.h"

t_world	*init_world(mlx_t *mlx, t_colors colors)
{
	t_world	*world;

	world = malloc(sizeof(t_world));
	if (!world)
		return (NULL);
	world->mlx = mlx;
	world->graphics = NULL;
	world->colors = colors;
	world->cf_img = gfx_create_image(mlx, &world->graphics, WIDTH, HEIGHT);
	world->drawing_board = gfx_create_image(mlx, &world->graphics, WIDTH,
			HEIGHT);
	world->door_img = gfx_create_image(mlx, &world->graphics, WIDTH, HEIGHT);
	return (world);
}

void	wd_render_cf(t_world *world)
{
	t_point	start;
	t_point	end;

	start = (t_point){0};
	end = (t_point){WIDTH, HEIGHT / 2};
	gfx_draw_rect(world->cf_img, start, end, world->colors.ccolor);
	start = (t_point){0, HEIGHT / 2};
	end = (t_point){WIDTH, HEIGHT};
	gfx_draw_rect(world->cf_img, start, end, world->colors.fcolor);
	mlx_image_to_window(world->mlx, world->crosshair, (WIDTH / 2)
		- (world->crosshair->width / 2), HEIGHT / 2);
}

void	wd_render_walls(t_world *world, t_ray_dat rays_info)
{
	int				y;
	int				color;
	double			scale_factor;
	t_render_info	info;
	t_wd_texture	texture;

	texture = wd_texture_bydirection(world, rays_info.direction);
	info = wd_calc_render_info(rays_info, texture);
	scale_factor = ((double)texture.img->height / info.wall_strip_height);
	y = info.wall_top_pixel;
	while (y < info.wall_bot_pixel - 1)
	{
		info.tex_offset_y = (info.pixel_offset++) * scale_factor;
		color = texture.pixels[info.tex_offset_y][info.tex_offset_x];
		mlx_put_pixel(world->drawing_board, rays_info.current_column, y++,
			color);
	}
}

void	wd_render_doors(t_world *world, t_ray_dat rays_info)
{
	int				y;
	int				color;
	double			scale_factor;
	t_wd_texture	texture;
	t_render_info	info;

	texture = world->textures.door_texture;
	info = wd_calc_render_info(rays_info, texture);
	scale_factor = ((double)texture.img->height / info.wall_strip_height);
	y = info.wall_top_pixel;
	while (y < info.wall_bot_pixel - 1)
	{
		info.tex_offset_y = (info.pixel_offset++) * scale_factor;
		color = texture.pixels[info.tex_offset_y][info.tex_offset_x];
		mlx_put_pixel(world->door_img, rays_info.current_column, y++, color);
	}
}
