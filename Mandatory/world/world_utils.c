/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:28:25 by helarras          #+#    #+#             */
/*   Updated: 2025/03/06 21:49:25 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/world.h"
#include "../include/raycaster.h"

int	wd_get_texture_color(t_world *world, mlx_image_t *texture, int x, int y)
{
	int texel_color;
	uint32_t **pixels = world->textures.north_pixels;
	// texel_color = ((texture->width * y) + x) * 4;
	return (pixels[y][x]);
}

mlx_image_t *wd_texture_bydirection(t_world *world, char direction)
{
	if (direction == 'N')
		return (world->textures.north_texture);
	if (direction == 'S')
		return (world->textures.south_texture);
	if (direction == 'E')
		return (world->textures.east_texture);
	if (direction == 'W')
		return (world->textures.west_texture);
	return (world->textures.north_texture);
}

t_render_info wd_calc_render_info(t_ray_dat rays_info)
{
	int projection;
	t_render_info render_info;
	
	projection = (WIDTH / 2) / tan(RADIANS(FOV / 2));
	// wall strip height
	render_info.wall_strip_height = (TILE_SIZE / rays_info.distance) * projection;
	// wall top pixel
	render_info.wall_top_pixel = (HEIGHT / 2) - (render_info.wall_strip_height / 2);
	if (render_info.wall_top_pixel < 0)
		render_info.wall_top_pixel = 0;
	// wall bot pixel
	render_info.wall_bot_pixel = (HEIGHT / 2) + (render_info.wall_strip_height / 2);
	if (render_info.wall_bot_pixel > HEIGHT)
		render_info.wall_bot_pixel = HEIGHT;
	// texture offset x
	if (rays_info.ver_hor == 'V')
		render_info.tex_offset_x = (int)rays_info.hitp.y % TILE_SIZE;
	else
		render_info.tex_offset_x = (int)rays_info.hitp.x % TILE_SIZE;
	return (render_info);
}