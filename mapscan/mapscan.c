/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapscan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:09:53 by helarras          #+#    #+#             */
/*   Updated: 2024/12/02 16:01:47 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"

t_mapscan	*init_mapscan(char *mapfile)
{
	t_mapscan *mapscan;

	mapscan = malloc(sizeof(t_mapscan));
	if (!mapscan)
		return (NULL);
	// if (chk_format(mapfile))
	// {
	// 	mp_post_error(ERR_FILE_FORMAT);
	// 	return (NULL);
	// }
	mapscan->mapfd = open(mapfile, O_RDONLY, 0777);
	// if (mapscan->mapfd < 0)
	// 	mp_post_error(ERR_FILE_READ);
	mapscan->map = NULL;
	mapscan->textures = NULL;
	mapscan->floor = 0;
	mapscan->ceilling = 0;
	return (mapscan);
}

void	mp_loadmap(t_mapscan *mapscan)
{
	char	*line;

	if (!rdr_read_data(mapscan))
	{
		
		return; // TODO: Handle data missing or unexpected error occured.
	}
	mapscan->map = rdr_readmap(mapscan);
	printf("floor: %s | ceilling: %s\n", mapscan->floor, mapscan->ceilling);
	t_list *current = mapscan->textures;
	while (current) {
		t_entry *entry = current->content; 
		printf("id: %c | path: %s\n", entry->id, entry->value);
		current = current->next;
	}
	int i = 0;
	while (mapscan->map[i])
	{
		printf("%s", mapscan->map[i++]);
	}
	printf("\n");
	
	system("leaks -q cub3D");
	exit(0);
	
}

void	mp_verifymap(t_mapscan *mapscan)
{
	
}

void	mp_post_error(t_mperror error)
{
	
}
