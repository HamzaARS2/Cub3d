/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:49 by helarras          #+#    #+#             */
/*   Updated: 2025/01/08 15:46:01 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/game.h"

void	gfx_set_color(mlx_image_t *image, int color)
{
	int y;
	int x;
	
	y = 0;
	while (y < image->height - 1)
	{
		x = 0;
		while (x < image->width - 1)
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

mlx_image_t	*gfx_create_image(t_game *game, int width, int height, int color)
{
	mlx_image_t	*image;

	image = mlx_new_image(game->mlx, width, height);
	if (!image)
		return (NULL);
	gfx_set_color(image, color);
	ft_lstadd_back(&game->graphics, ft_lstnew(image));
	return (image);
}

// TODO: function to clear allocated images.