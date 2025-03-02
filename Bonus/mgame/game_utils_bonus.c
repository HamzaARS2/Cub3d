/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:31:47 by helarras          #+#    #+#             */
/*   Updated: 2024/12/20 08:37:26 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game_bonus.h"

// Remove later!
void	print_map(t_mapscan *mapscan)
{
	printf("floor: %s | ceilling: %s\n", mapscan->colors.fcolor_str, mapscan->colors.ccolor_str);
	
	printf("id: %c | path: %s\n", 'N', mapscan->textures.north_tex);
	printf("id: %c | path: %s\n", 'S', mapscan->textures.south_tex);
	printf("id: %c | path: %s\n", 'E', mapscan->textures.east_tex);
	printf("id: %c | path: %s\n", 'W', mapscan->textures.west_tex);

	int i = 0;
	while (mapscan->map[i])
	{
		printf("%s\n", mapscan->map[i++]);
	}
	printf("\n");
}

t_mapscan	*readmap(char *mapfile)
{
	t_mapscan *mapscan;

	mapscan = init_mapscan(mapfile);
	if (!mapscan)
		return (NULL);
	mp_loadmap(mapscan);
	if (!mp_verifymap(mapscan))
	{
		mp_clearmap(mapscan);
		exit(EXIT_FAILURE);
	}
	print_map(mapscan); // Remove later!
	return (mapscan);
}
