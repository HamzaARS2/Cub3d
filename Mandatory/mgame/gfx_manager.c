/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:49 by helarras          #+#    #+#             */
/*   Updated: 2025/03/05 19:06:36 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/game.h"

void	gfx_set_color(mlx_image_t *image, t_point coords, int color)
{
	int y;
	int x;
	
	coords.x *= TILE_SIZE;
	coords.y *= TILE_SIZE;
	y = coords.y;
	while (y < coords.y + TILE_SIZE - 1)
	{
		x = coords.x;
		while (x < coords.x + TILE_SIZE - 1)
			mlx_put_pixel(image, x++, y, color);
		y++;
	}
}

mlx_image_t	*gfx_create_teximage(mlx_t *mlx, t_list *graphics, char *tex_path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	
	texture = mlx_load_png(tex_path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(mlx, texture);
	ft_lstadd_back(&graphics, ft_lstnew(image));
	mlx_delete_texture(texture);
	return (image);
}

mlx_image_t	*gfx_create_image(mlx_t *mlx, t_list *graphics, int width, int height)
{
	mlx_image_t	*image;

	image = mlx_new_image(mlx, width, height);
	if (!image)
		return (NULL);
	ft_lstadd_back(&graphics, ft_lstnew(image));
	return (image);
}

// TODO: function to clear allocated images.