/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_manager.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:31:20 by helarras          #+#    #+#             */
/*   Updated: 2025/03/06 13:49:13 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_MANAGER_BONUS_H
# define GFX_MANAGER_BONUS_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "../../libft/libft.h"

mlx_image_t	*gfx_create_teximage(mlx_t *mlx, t_list **graphics, char *tex_path);
mlx_image_t	*gfx_create_image(mlx_t *mlx, t_list **graphics, int width, int height);
void		gfx_set_color(mlx_image_t *image, t_point coords, int color);
void	gfx_draw_rect(mlx_image_t *img, t_point start, t_point end , int color);

#endif