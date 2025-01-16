/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:49 by helarras          #+#    #+#             */
/*   Updated: 2025/01/14 16:39:23 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/game.h"

void	gfx_set_color(mlx_image_t *image, t_vector2 coords, int color)
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

mlx_image_t	*gfx_create_teximage(t_game *game, char *tex_path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	
	texture = mlx_load_png(tex_path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(game->mlx, texture);
	ft_lstadd_back(&game->graphics, ft_lstnew(image));
	mlx_delete_texture(texture);
	return (image);
}

mlx_image_t	*gfx_create_image(t_game *game, int width, int height)
{
	mlx_image_t	*image;

	image = mlx_new_image(game->mlx, width, height);
	if (!image)
		return (NULL);
	ft_lstadd_back(&game->graphics, ft_lstnew(image));
	return (image);
}

// TODO: function to clear allocated images.