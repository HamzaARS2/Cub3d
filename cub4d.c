/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub4d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:23:56 by helarras          #+#    #+#             */
/*   Updated: 2024/11/21 12:07:26 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub4d.h"

mlx_image_t *img;

static void	hook(void *param) {
	 mlx_t *mlx = param;
	
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		img->instances[0].x += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		img->instances[0].x -= 5;
}


int	main() {
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Cub4D", true);
	if (!mlx)
		return (EXIT_FAILURE);
	img = mlx_new_image(mlx, 100, 100);
	
	mlx_image_to_window(mlx, img, 0, 0);
	for (int y = 0; y < 100; y++)
		for (int x = 0; x < 100; x++)
			mlx_put_pixel(img, x, y, 0xFFFFFFFF);
	mlx_loop_hook(mlx, hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}