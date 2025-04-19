/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapscan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:09:53 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 11:33:42 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"

t_mapscan	*init_mapscan(char *mapfile)
{
	t_mapscan	*mapscan;

	mapscan = malloc(sizeof(t_mapscan));
	if (!mapscan)
		return (NULL);
	if (!chk_format(mapfile))
	{
		free(mapscan);
		return (NULL);
	}
	mapscan->mapfd = open(mapfile, O_RDONLY, 0777);
	if (mapscan->mapfd < 0)
	{
		free(mapscan);
		mp_post_error(ERR_FILE_READ);
		return (NULL);
	}
	mapscan->map = NULL;
	mapscan->mapsize = (t_point){0};
	mapscan->texpaths = (t_texpath){0};
	mapscan->error = NO_ERROR;
	mapscan->colors = (t_colors){0};
	return (mapscan);
}

void	mp_loadmap(t_mapscan *mapscan)
{
	if (!rdr_read_data(mapscan))
	{
		mp_post_error(mapscan->error);
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
	t_point	start_pos;

	if (!chk_color(mapscan->colors.fcolor_str, &mapscan->colors.fcolor)
		|| !chk_color(mapscan->colors.ccolor_str, &mapscan->colors.ccolor))
	{
		mp_post_error(ERR_INVALID_COLOR);
		return (false);
	}
	if (!chk_map(mapscan))
		return (false);
	start_pos = mapscan->start_pos;
	mapscan->c_direction = mapscan->map[start_pos.y][start_pos.x];
	return (true);
}

bool	mp_post_error(t_mperror error)
{
	if (error == ERR_INVALID_DATA)
		ft_putstr_fd("Error\nInvalid data!.\n", 2);
	else if (error == ERR_MISSING_DATA)
		ft_putstr_fd("Error\nMissing data!.\n", 2);
	else if (error == ERR_DUPLICATED_DATA)
		ft_putstr_fd("Error\nDuplicated data!.\n", 2);
	else if (error == ERR_MAP_NOT_FOUND)
		ft_putstr_fd("Error\nMap not found!.\n", 2);
	else if (error == ERR_FILE_FORMAT)
		ft_putstr_fd("Error\nWrong file format!.\n", 2);
	else if (error == ERR_FILE_READ)
		ft_putstr_fd("Error\nCan't read file!.\n", 2);
	else if (error == ERR_INVALID_COLOR)
		ft_putstr_fd("Error\nInvalid color!.\n", 2);
	else if (error == ERR_INVALID_MAP)
		ft_putstr_fd("Error\nInvalid map!.\n", 2);
	else if (error == ERR_MULTIPLE_START)
		ft_putstr_fd("Error\nMultiple starting positions!.\n", 2);
	else if (error == ERR_NO_START)
		ft_putstr_fd("Error\nNo starting position found!.\n", 2);
	else if (error == ERR_MAP_NOT_CLOSED)
		ft_putstr_fd("Error\nMap not closed!.\n", 2);
	else if (error == ERR_INVALID_CHAR)
		ft_putstr_fd("Error\nInvalid map component!.\n", 2);
	return (!error);
}

void	mp_clearmap(t_mapscan *mapscan)
{
	int	i;

	i = 0;
	if (!mapscan)
		return ;
	free(mapscan->texpaths.north_tex);
	free(mapscan->texpaths.south_tex);
	free(mapscan->texpaths.east_tex);
	free(mapscan->texpaths.west_tex);
	free(mapscan->colors.fcolor_str);
	free(mapscan->colors.ccolor_str);
	while (mapscan->map && mapscan->map[i])
	{
		free(mapscan->map[i]);
		mapscan->map[i++] = NULL;
	}
	free(mapscan->map);
	ft_memset(mapscan, 0, sizeof(t_mapscan));
	free(mapscan);
}
