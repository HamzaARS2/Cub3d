/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub4d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:23:56 by helarras          #+#    #+#             */
/*   Updated: 2024/12/03 10:57:26 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub4d.h"

t_mapscan	*readmap(char *mapfile)
{
	t_mapscan *mapscan;

	mapscan = init_mapscan(mapfile);
	mp_loadmap(mapscan);
	return (mapscan);
}

void	foo() {
	system("leaks -q cub3D");
}

int	main(int ac, char **av) {
	t_mapscan *mapscan;

	atexit(foo);
	mapscan = readmap(av[1]);
	mp_clearmap(mapscan);
	// mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "Cub4D", true);
	// if (!mlx)
	// 	return (EXIT_FAILURE);

	
	// // mlx loop.
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
