/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:23:16 by helarras          #+#    #+#             */
/*   Updated: 2024/12/07 10:50:23 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"

int	rdr_checkid(char *line)
{
	int i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i] && line[i + 1])
	{
		if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "SO", 2)
			|| !ft_strncmp(line + i, "EA", 2) || !ft_strncmp(line + i, "WE", 2)
			|| line[i] == 'F' || line[i] == 'C')
			return (i);
		if (ft_isprint(line[i]) && line[i] != 32)
			break;
		i++;
	}
	return (-1);
}

bool	rdr_readtex(t_mapscan *mapscan, char *line)
{
	int id;

	id = rdr_checkid(line);
	if (id < 0 || (line[id] != 'N' && line[id] != 'S'
		&& line[id] != 'E' && line[id] != 'W'))
		return (false);
	if ((line[id + 2] < 9 || line[id + 2] > 13) && line[id + 2] != 32)
		return (false);
	if (line[id] == 'N')
		mapscan->textures.north_tex = ft_strtrim(line + id + 2, " \n\t");
	else if (line[id] == 'S')
		mapscan->textures.south_tex = ft_strtrim(line + id + 2, " \n\t");
	else if (line[id] == 'E')
		mapscan->textures.east_tex = ft_strtrim(line + id + 2, " \n\t");
	else if (line[id] == 'W')
		mapscan->textures.west_tex = ft_strtrim(line + id + 2, " \n\t");
	return (true);
}

bool	rdr_readsurfs(t_mapscan *mapscan, char *line)
{
	int id;

	id = rdr_checkid(line);
	if (id < 0 || (line[id] != 'F' && line[id] != 'C'))
		return (false);
	if ((line[id + 1] < 9 && line[id + 1] > 13) && line[id + 1] != 32)
		return (false);
	if (line[id] == 'F')
		mapscan->floor = ft_strtrim(line + id + 1, "  \n\t");
	else
		mapscan->ceilling = ft_strtrim(line + id + 1, " \n\t");
	return (true);
}

bool	rdr_read_data(t_mapscan *mapscan)
{
	char	*line;
	int		count;
	bool	flag;
	
	count = 6;
	flag = false;
	while (count && !flag)
	{
		line = get_next_line(mapscan->mapfd);
		if (!line)
			return (false);
		if (rdr_readtex(mapscan, line))
			count--;
		else if (rdr_readsurfs(mapscan, line))
			count--;
		else if (count > 0 && !ump_is_empty_line(line))
			flag = true;
		free(line);
		line = NULL;
	}
	return (flag);
}

char	**rdr_readmap(t_mapscan *mapscan)
{
	t_list	*maplst;
	char	*line;
	int		mapsize;
	bool	mapstarted;
	
	mapsize = 0;
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
		ft_lstadd_back(&maplst, ft_lstnew(line));
		mapsize++;
	}
	return (ump_create_map(maplst, mapsize));
}

