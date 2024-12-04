/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapscan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:09:53 by helarras          #+#    #+#             */
/*   Updated: 2024/12/04 12:14:24 by helarras         ###   ########.fr       */
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
	if (mapscan->mapfd < 0)
		mp_post_error(ERR_FILE_READ);
	mapscan->map = NULL;
	mapscan->textures = NULL;
	mapscan->floor = 0;
	mapscan->ceilling = 0;
	return (mapscan);
}



void	mp_loadmap(t_mapscan *mapscan)
{
	char	*line;
	
	if (rdr_read_data(mapscan))
	{
		mp_post_error(ERR_INVALID_DATA);
		exit(EXIT_FAILURE);
	}
	mapscan->map = rdr_readmap(mapscan);
	if (!mapscan->map)
	{
		mp_post_error(ERR_MAP_NOT_FOUND);
		exit(EXIT_FAILURE);
	}
}

bool	mp_verifymap(t_mapscan *mapscan)
{
	int			i;
	t_mperror	error[15];

	i = 0;
	error[i++] = chk_textures(mapscan->textures);
	if (error[0])
		mp_post_error(error[0]);
	return (!error[0]);
}

void	mp_clearmap(t_mapscan *mapscan)
{
	int i;

	i = 0;
	ft_lstclear(&mapscan->textures, ump_clear);
	free(mapscan->floor);
	free(mapscan->ceilling);
	while (mapscan->map && mapscan->map[i])
	{
		free(mapscan->map[i]);
		mapscan->map[i++] = NULL;
	}
	free(mapscan->map);
	ft_memset(mapscan, 0, sizeof(t_mapscan));
}

void	mp_post_error(t_mperror error)
{
	if (error == ERR_INVALID_DATA)
		ft_putstr_fd("Error\nInvalid data!.\n", 2);
	else if (error == ERR_MISSING_TEXTURE)
		ft_putstr_fd("Error\nMissing texture!.\n", 2);
	else if (error == ERR_DUPLICATED_TEXTURE)
		ft_putstr_fd("Error\nduplicated texture\n", 2);
	else if (error == ERR_MAP_NOT_FOUND)
		ft_putstr_fd("Error\nMap not found!.\n", 2);

}
