/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_manager_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:31:20 by helarras          #+#    #+#             */
/*   Updated: 2025/04/17 19:02:58 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_MANAGER_BONUS_H
# define GFX_MANAGER_BONUS_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../libft/libft.h"
# include "world_bonus.h"

mlx_image_t	*gfx_create_teximage(mlx_t *mlx, t_list **graphics, char *tex_path);
mlx_image_t	*gfx_create_image(mlx_t *mlx, t_list **graphics, int width,
				int height);
void		gfx_draw_rect(mlx_image_t *img, t_point start, t_point end,
				int color);
void		gfx_clear(mlx_t *mlx, t_list **graphics);

#endif