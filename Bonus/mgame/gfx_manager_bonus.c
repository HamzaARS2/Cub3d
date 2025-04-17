/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx_manager_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:42:49 by helarras          #+#    #+#             */
/*   Updated: 2025/04/17 11:04:38 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/game_bonus.h"

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
	if (!texture) {
		ft_putstr_fd("Error\nLoading png failed!\n", 2);
		return (NULL);
	}
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
	t_list *current;
	
	current = *graphics;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
		temp = NULL;
	}
}