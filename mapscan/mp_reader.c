/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:23:16 by helarras          #+#    #+#             */
/*   Updated: 2024/12/02 16:34:42 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"

bool	rdr_readtex(t_mapscan *mapscan, char *line)
{
	t_entry	*entry;

	if (!line  || (ft_strncmp(line, "NO", 2) && ft_strncmp(line, "SO", 2)
		&& ft_strncmp(line, "WE", 2) && ft_strncmp(line, "EA", 2)))
		return (false);
	entry = malloc(sizeof(t_entry));
	if (!entry)
		return (false);
	entry->id = line[0];
	entry->value = ft_strtrim(line + 2, " \n");
	ft_lstadd_back(&mapscan->textures, ft_lstnew(entry));
	return (true);
}

bool	rdr_readsurfs(t_mapscan *mapscan, char *line)
{		
	if (!line || (line[0] != 'F' && line[0] != 'C'))
		return (false);
	if (line[0] == 'F')
		mapscan->floor = ft_strtrim(line + 1, " \n");
	else
		mapscan->ceilling = ft_strtrim(line + 1, " \n");
	return (true);
}

bool	rdr_read_data(t_mapscan *mapscan)
{
	char	*line;
	int		count;

	count = 6;
	while (count)
	{
		line = get_next_line(mapscan->mapfd);
		if (!line)
			return (false);
		if (rdr_readtex(mapscan, line) || rdr_readsurfs(mapscan, line) || ump_is_empty_line(line))
			count--;
		free(line);
		line = NULL;
	}
	return (true);
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
