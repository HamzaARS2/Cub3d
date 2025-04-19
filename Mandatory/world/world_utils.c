/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:28:25 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 11:07:28 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/raycaster.h"
#include "../include/world.h"

t_wd_texture	wd_texture_bydirection(t_world *world, char direction)
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

void	wd_calc_wall_bounds(t_render_info *render_info)
{
	render_info->wall_top_pixel = (HEIGHT / 2) - (render_info->wall_strip_height
			/ 2);
	render_info->pixel_offset = 0;
	if (render_info->wall_top_pixel < 0)
	{
		render_info->pixel_offset = -render_info->wall_top_pixel;
		render_info->wall_top_pixel = 0;
	}
	render_info->wall_bot_pixel = (HEIGHT / 2) + (render_info->wall_strip_height
			/ 2);
	if (render_info->wall_bot_pixel > HEIGHT)
		render_info->wall_bot_pixel = HEIGHT;
}

t_render_info	wd_calc_render_info(t_ray_dat rays_info, t_wd_texture texture)
{
	int				projection;
	t_render_info	render_info;
	double			offset_x;

	projection = (WIDTH / 2) / tan(radians(FOV / 2));
	render_info.wall_strip_height = (TILE_SIZE / rays_info.distance)
		* projection;
	wd_calc_wall_bounds(&render_info);
	if (rays_info.ver_hor == 'V')
	{
		offset_x = (rays_info.hitp.y / TILE_SIZE);
		render_info.tex_offset_x = (offset_x - floor(offset_x))
			* texture.img->width;
	}
	else
	{
		offset_x = (rays_info.hitp.x / TILE_SIZE);
		render_info.tex_offset_x = (offset_x - floor(offset_x))
			* texture.img->width;
	}
	return (render_info);
}

uint32_t	**wd_get_color_buffer(mlx_image_t *texture)
{
	int			i;
	int			y;
	int			x;
	uint32_t	**pixels;

	i = 0;
	pixels = malloc((texture->height + 1) * sizeof(uint32_t *));
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
			pixels[y][x++] = get_rgba(texture->pixels[i], texture->pixels[i
					+ 1], texture->pixels[i + 2], texture->pixels[i + 3]);
			i += 4;
		}
	}
	pixels[y] = NULL;
	return (pixels);
}

void	wd_clear(t_world *world)
{
	if (!world)
		return ;
	gfx_clear(world->mlx, &world->graphics);
	ft_clear_array((void **)world->textures.north_texture.pixels);
	ft_clear_array((void **)world->textures.south_texture.pixels);
	ft_clear_array((void **)world->textures.east_texture.pixels);
	ft_clear_array((void **)world->textures.west_texture.pixels);
	free(world);
}
