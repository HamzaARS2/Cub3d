/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:31:20 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 11:36:25 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_MANAGER_H
# define GFX_MANAGER_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../libft/libft.h"
# include "world.h"

mlx_image_t	*gfx_create_teximage(mlx_t *mlx, t_list **graphics, char *tex_path);
mlx_image_t	*gfx_create_image(mlx_t *mlx, t_list **graphics, int width,
				int height);
void		gfx_draw_rect(mlx_image_t *img, t_point start, t_point end,
				int color);
void		gfx_clear(t_list **graphics);

#endif