/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:28:25 by helarras          #+#    #+#             */
/*   Updated: 2025/03/08 21:39:41 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/world.h"
#include "../include/raycaster.h"

t_wd_texture wd_texture_bydirection(t_world *world, char direction)
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

t_render_info wd_calc_render_info(t_ray_dat rays_info, t_wd_texture texture)
{
	int projection;
	t_render_info render_info;
	double offset_x;
	
	projection = (WIDTH / 2) / tan(RADIANS(FOV / 2));
	// wall strip height
	render_info.wall_strip_height = (TILE_SIZE / rays_info.distance) * projection;
	// wall top pixel
	render_info.wall_top_pixel = (HEIGHT / 2) - (render_info.wall_strip_height / 2);
	// if (render_info.wall_top_pixel < 0) {
	// 	render_info.wall_top_pixel = abs(render_info.wall_top_pixel);
	// }
	// wall bot pixel
	render_info.wall_bot_pixel = (HEIGHT / 2) + (render_info.wall_strip_height / 2);
	if (render_info.wall_bot_pixel > HEIGHT)
		render_info.wall_bot_pixel = HEIGHT;
	// texture offset x
	if (rays_info.ver_hor == 'V') {
		offset_x = (rays_info.hitp.y / TILE_SIZE);
		render_info.tex_offset_x = (offset_x - floor(offset_x)) * texture.img->width;
	}
	else {
		offset_x = (rays_info.hitp.x / TILE_SIZE);
		render_info.tex_offset_x = (offset_x - floor(offset_x)) * texture.img->width;
	}
	return (render_info);
}

static void	*free_array(void **array, int i)
{
	while (i >= 0 && array[i])
		free(array[i--]);
	free(array);
	return (NULL);
}


uint32_t **wd_get_color_buffer(mlx_image_t *texture)
{
	int i;
	int y;
	int x;
	uint32_t **pixels;

	i = 0;
	pixels = malloc(texture->height * sizeof(uint32_t *));
	if (!pixels)
		return (NULL);
	y = -1;
	while (++y < texture->height)
	{
		pixels[y] = malloc(texture->width * sizeof(uint32_t));
		if (!pixels[y])
			return (free_array((void **)pixels, y - 1));
		x = 0;
		while (x < texture->width)
		{
			pixels[y][x++] = get_rgba(texture->pixels[i], texture->pixels[i + 1], texture->pixels[i + 2], texture->pixels[i + 3]);
			i += 4;
		}
	}
	return (pixels);
}

