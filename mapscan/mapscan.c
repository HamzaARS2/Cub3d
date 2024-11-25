/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapscan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:09:53 by helarras          #+#    #+#             */
/*   Updated: 2024/11/25 13:11:07 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/mapscan.h"

t_mapscan	*init_mapscan(char *mapfile)
{
	t_mapscan *mapscan;

	mapscan = malloc(sizeof(t_mapscan));
	if (!mapscan)
		return (NULL);
	mapscan->map = NULL;
	mapscan->line = NULL;
	mapscan->error = NO_ERROR;
	mapscan->i = 0;
}

void	mp_loadmap(t_mapscan *mapscan, char *mapfile)
{
	int	mapfd;

	if (chk_format(mapfile))
		return (mp_post_error(ERR_FILE_FORMAT));
	mapfd = open(mapfile, O_RDONLY);
	if (mapfd < 0)
		mp_post_error(ERR_FILE_READ);
	
}

void	mp_verifymap(t_mapscan *mapscan)
{
	
}

void	mp_post_error(t_mperror error)
{
	
}
