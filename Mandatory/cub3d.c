/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:23:56 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 14:02:37 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

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
	run_game(&game);
	cleanup_game(game);
	return (EXIT_SUCCESS);
}
