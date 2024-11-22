/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub4d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:23:56 by helarras          #+#    #+#             */
/*   Updated: 2024/11/22 20:53:09 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub4d.h"

mlx_image_t *img;
mlx_image_t *red_bar;
mlx_image_t *green_bar;
mlx_image_t *blue_bar;
mlx_image_t *selector;

int r = 255;
int g = 255;
int b = 255;
int a = 255;
int	get_rgba(int r, int g, int b, int a) {
	return (r << 24 | g << 16 | b << 8 | a);
}
	// 0010 1010 0000 0000 0000 0000 0000 0000
	// 0000 0000 1111 1111 0000 0000 0000 0000
	// 0000 0000 0000 0000 0010 0110 0000 0000
	// 0000 0000 0000 0000 0000 0000 0100 0100
	// 0010 1010 1111 1111 0010 0110 0100 0100

void	set_image_color(mlx_image_t *img, int width, int height, int color) {
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			mlx_put_pixel(img, x, y, color);
}
static void	hook(void *param) {
	 mlx_t *mlx = param;
	
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		r -= 1;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		g -= 1;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		b -= 1;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		a -= 1;
	set_image_color(img, 100, 100, get_rgba(r, g, b, a));
}

void	draw_bars(mlx_t *mlx) {
	red_bar = mlx_new_image(mlx, 255, 25);
	green_bar = mlx_new_image(mlx, 255, 25);
	blue_bar = mlx_new_image(mlx, 255, 25);

	mlx_image_to_window(mlx, red_bar, WIDTH / 2, 25);
	set_image_color(red_bar, 255, 25, get_rgba(255, 0, 0, 255));

	mlx_image_to_window(mlx, green_bar, WIDTH / 2, 60);
	set_image_color(green_bar, 255, 25, get_rgba(0, 255, 0, 255));
	
	mlx_image_to_window(mlx, blue_bar, WIDTH / 2, 95);
	set_image_color(blue_bar, 255, 25, get_rgba(0, 0, 255, 255));
}

void	draw_selectors(mlx_t *mlx) {
	int start_x = red_bar->instances[0].x;
	int end_x = start_x + red_bar->width;
	
	int x_pos = start_x;
	int y_pos = 25;
	
	selector = mlx_new_image(mlx, 10, 30);
	mlx_image_to_window(mlx, selector, x_pos, y_pos);
	set_image_color(selector, selector->width, selector->height, get_rgba(255, 255, 255, 255));
}

int	main() {
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Cub4D", true);
	if (!mlx)
		return (EXIT_FAILURE);
	img = mlx_new_image(mlx, 100, 100);
	
	mlx_image_to_window(mlx, img, 0, 0);
	set_image_color(img, 100, 100, get_rgba(r, g, b, a));
	draw_bars(mlx);
	draw_selectors(mlx);
	mlx_loop_hook(mlx, hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
