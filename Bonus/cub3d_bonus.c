/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:23:56 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 14:02:48 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d_bonus.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nOne argument required!\n", 2);
		return (EXIT_FAILURE);
	}
	if (!init_game(&game, av[1]))
	{
		cleanup_game(game);
		return (EXIT_FAILURE);
	}
	mlx_set_mouse_pos(game.mlx, WIDTH / 2, HEIGHT / 2);
	mlx_get_mouse_pos(game.mlx, &game.mouse_pos.x, &game.mouse_pos.y);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_DISABLED);
	run_game(&game);
	cleanup_game(game);
	return (EXIT_SUCCESS);
}
