/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:07:49 by helarras          #+#    #+#             */
/*   Updated: 2025/03/03 14:25:03 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "mapscan.h"
# include "gfx_manager.h"
# include "../../MLX42/include/MLX42/MLX42.h"

# define TILE_SIZE 32
# define OBJ_SIZE 4

typedef struct s_textures {
	mlx_image_t *north_texture;
	mlx_image_t *south_texture;
	mlx_image_t *east_texture;
	mlx_image_t *west_texture;
} t_textures;

typedef struct s_world {
	mlx_t		*mlx;
	t_list		*graphics;
	t_colors	colors;
	t_textures	textures;
} t_world;

t_world *init_world(mlx_t *mlx, t_colors colors);

t_textures	wd_load_textures(t_world *world, t_texpath texpaths);


#endif