/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:23:56 by helarras          #+#    #+#             */
/*   Updated: 2025/04/18 10:51:33 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	foo(void)
{
	system("leaks -q cub3D");
}

int	main(int ac, char **av)
{
	t_game	game;

	(void) ac;
	atexit(foo);
	if (!init_game(&game, av[1]))
	{
		cleanup_game(game);
		return (EXIT_FAILURE);
	}
	run_game(&game);
	cleanup_game(game);
	return (EXIT_SUCCESS);
}
