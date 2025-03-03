/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:23:16 by helarras          #+#    #+#             */
/*   Updated: 2025/02/21 18:54:51 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan_bonus.h"

// Checks for data id in the line string.
// Can Post invalid data error if the id is not correct.
// Return -1 if it couldnt find id or an index it it did.
int	rdr_checkid(t_mapscan *mapscan, char *line)
{
	int i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i] && !mapscan->error)
	{
		if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "SO", 2)
			|| !ft_strncmp(line + i, "EA", 2) || !ft_strncmp(line + i, "WE", 2)
			|| line[i] == 'F' || line[i] == 'C')
			return (i);
		if (ft_isprint(line[i]) && line[i] != 32)
			mapscan->error = ERR_INVALID_DATA;
		i++;
	}
	return (-1);
}

// Can post duplication error.
bool	rdr_readtex(t_mapscan *mapscan, char *line)
{
	int id;

	id = rdr_checkid(mapscan, line);
	if (id < 0 || (line[id] != 'N' && line[id] != 'S'
		&& line[id] != 'E' && line[id] != 'W'))
		return (false);
	if ((line[id + 2] < 9 || line[id + 2] > 13) && line[id + 2] != 32)
		return (false);
	if (line[id] == 'N' && !mapscan->texpaths.north_tex)
		mapscan->texpaths.north_tex = ft_strtrim(line + id + 2, " \n\t");
	else if (line[id] == 'S' && !mapscan->texpaths.south_tex)
		mapscan->texpaths.south_tex = ft_strtrim(line + id + 2, " \n\t");
	else if (line[id] == 'E' && !mapscan->texpaths.east_tex)
		mapscan->texpaths.east_tex = ft_strtrim(line + id + 2, " \n\t");
	else if (line[id] == 'W' && !mapscan->texpaths.west_tex)
		mapscan->texpaths.west_tex = ft_strtrim(line + id + 2, " \n\t");
	else
		mapscan->error = ERR_DUPLICATED_DATA;
	return (true);
}

bool	rdr_readsurfs(t_mapscan *mapscan, char *line)
{
	int id;

	id = rdr_checkid(mapscan, line);
	if (id < 0 || (line[id] != 'F' && line[id] != 'C'))
		return (false);
	if (!ft_iswhitespace(line[id + 1]))
		return (false);
	if (line[id] == 'F' && !mapscan->colors.fcolor_str)
		mapscan->colors.fcolor_str = ft_strtrim(line + id + 1, " \n\t");
	else if (line[id] == 'C' && !mapscan->colors.ccolor_str)
		mapscan->colors.ccolor_str = ft_strtrim(line + id + 1, " \n\t");
	else
		mapscan->error = ERR_DUPLICATED_DATA;
	return (true);
}

bool	rdr_read_data(t_mapscan *mapscan)
{
	char	*line;
	int		count;
	
	count = 6;
	while (count && !mapscan->error)
	{
		line = get_next_line(mapscan->mapfd);
		if (!line)
		{
			mapscan->error = ERR_INVALID_MAP;
			return (false);
		}
		if (rdr_readtex(mapscan, line))
			count--;
		else if (rdr_readsurfs(mapscan, line))
			count--;
		else if (count > 0 && !ump_is_empty_line(line) && !mapscan->error)
			mapscan->error = ERR_INVALID_DATA;
		free(line);
		line = NULL;
	}
	return (!mapscan->error);
}

char	**rdr_readmap(t_mapscan *mapscan)
{
	t_list	*maplst;
	char	*line;
	bool	mapstarted;
	
	maplst = NULL;
	mapstarted = false;
	while (true)
	{
		line = get_next_line(mapscan->mapfd);
		if (!line)
			break;
		if (!mapstarted && ump_is_empty_line(line))
		{
			free(line);
			continue;
		}
		mapstarted = true;
		ft_lstadd_back(&maplst, ft_lstnew(ft_strtrim(line, "\n")));
		free(line);
		mapscan->mapsize.y++;
	}
	mapscan->mapsize.x = ft_lstcontent_max(maplst);
	return (ump_create_map(maplst, mapscan->mapsize));
}

