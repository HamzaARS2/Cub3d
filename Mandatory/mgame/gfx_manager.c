/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:49 by helarras          #+#    #+#             */
/*   Updated: 2025/03/12 11:56:30 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/game.h"

void	gfx_draw_rect(mlx_image_t *img, t_point start, t_point end , int color)
{
	int x;
	int y;

	y = start.y;
	while (y < end.y)
	{
		x = start.x;
		while (x < end.x)
			mlx_put_pixel(img, x++, y, color);
		y++;
	}
}

mlx_image_t	*gfx_create_teximage(mlx_t *mlx, t_list **graphics, char *tex_path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;
	
	texture = mlx_load_png(tex_path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(mlx, texture);
	ft_lstadd_back(graphics, ft_lstnew(image));
	mlx_delete_texture(texture);
	return (image);
}

mlx_image_t	*gfx_create_image(mlx_t *mlx, t_list **graphics, int width, int height)
{
	mlx_image_t	*image;

	image = mlx_new_image(mlx, width, height);
	if (!image)
		return (NULL);
	ft_lstadd_back(graphics, ft_lstnew(image));
	return (image);
}

// TODO: function to clear allocated images.
void    gfx_clear(mlx_t *mlx, t_list **graphics)
{
	t_list *temp;
	mlx_image_t *current_img;

	while (*graphics)
	{
		current_img = (mlx_image_t *)(*graphics)->content;
		mlx_delete_image(mlx, current_img);
		temp = *graphics;
		*graphics = (*graphics)->next;
		free(temp);
		temp = NULL;
	}
}