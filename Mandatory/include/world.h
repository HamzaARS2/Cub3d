/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:29:18 by nhimad            #+#    #+#             */
/*   Updated: 2025/04/19 11:07:52 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "mapscan.h"

# define TILE_SIZE 32
# define OBJ_SIZE 4
# define CROSSHAIR_PATH "Mandatory/textures/crosshair/crosshair_64.png"

typedef struct s_vector2
{
	double			x;
	double			y;
}					t_vector2;

typedef struct s_ray_data
{
	t_vector2		hitp;
	char			ver_hor;
	char			direction;
	double			distance;
	int				current_column;
}					t_ray_dat;

typedef struct s_render_info
{
	double			wall_strip_height;
	int				wall_top_pixel;
	int				wall_bot_pixel;
	int				tex_offset_x;
	int				tex_offset_y;
	int				pixel_offset;
}					t_render_info;

typedef struct s_wd_texture
{
	mlx_image_t		*img;
	uint32_t		**pixels;
}					t_wd_texture;

typedef struct s_textures
{
	t_wd_texture	north_texture;
	t_wd_texture	south_texture;
	t_wd_texture	east_texture;
	t_wd_texture	west_texture;
}					t_textures;

typedef struct s_world
{
	mlx_t			*mlx;
	t_list			*graphics;
	t_colors		colors;
	t_textures		textures;
	mlx_image_t		*crosshair;
	mlx_image_t		*cf_img;
	mlx_image_t		*drawing_board;
}					t_world;

t_world				*init_world(mlx_t *mlx, t_colors colors);

bool				wd_load_textures(t_world *world, t_texpath texpaths);
void				wd_render_cf(t_world *world);
t_wd_texture		wd_texture_bydirection(t_world *world, char direction);
t_render_info		wd_calc_render_info(t_ray_dat rays_info,
						t_wd_texture texture);
void				wd_calc_wall_bounds(t_render_info *render_info);
void				wd_render_walls(t_world *world, t_ray_dat rays_info);
uint32_t			**wd_get_color_buffer(mlx_image_t *texture);
void				wd_prepare_colors(t_world *world);
void				wd_clear(t_world *world);
#endif