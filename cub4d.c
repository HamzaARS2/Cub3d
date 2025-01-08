/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub4d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhimad <nhimad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:23:56 by helarras          #+#    #+#             */
/*   Updated: 2025/01/07 14:08:53 by nhimad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub4d.h"

void	foo() {
	system("leaks -q cub3D");
}

int	main(int ac, char **av) {
	t_game		game;

	// atexit(foo);
	if (!init_game(&game, av[1]))
	{
		cleanup_game(game);
		return (EXIT_FAILURE);
	}
	//run_game(&game);
	t_graphic *images;
	while (game.graphics)
	{
		images = game.graphics->content;
		printf("%p\n",images);
		game.graphics = game.graphics->next;
	}

	cleanup_game(game);
	return (EXIT_SUCCESS);
}
