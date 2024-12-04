/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:23:16 by helarras          #+#    #+#             */
/*   Updated: 2024/12/04 16:11:29 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"

// bool	rdr_readtex(t_mapscan *mapscan, char *line)
// {
// 	t_entry	*entry;
// 	char	*tline;

// 	tline = ft_strtrim(line, " \n");
// 	if (!tline  || (ft_strncmp(tline, "NO ", 3) && ft_strncmp(tline, "SO ", 3)
// 		&& ft_strncmp(tline, "WE ", 3) && ft_strncmp(tline, "EA ", 3)))
// 		return (false);
// 	entry = malloc(sizeof(t_entry));
// 	if (!entry)
// 		return (false);
// 	entry->id = tline[0];
// 	entry->value = ft_strdup(tline + 3);
// 	if (!entry->value || !entry->value[0])
// 	{
// 		ump_clear(entry);
// 		return (false);
// 	}
// 	free(tline);
// 	ft_lstadd_back(&mapscan->textures, ft_lstnew(entry));
// 	return (true);
// }

bool	rdr_readtex(t_mapscan *mapscan, char *line)
{
	t_entry	*entry;
	char	**strs;

	strs = ft_split(line, 32);
	if (!strs)
		return (false);
	if (!strs[0]  || (ft_strncmp(strs[0], "NO", 2) && ft_strncmp(strs[0], "SO", 2)
		&& ft_strncmp(strs[0], "WE", 2) && ft_strncmp(strs[0], "EA", 2)))
		return (false);
	entry = malloc(sizeof(t_entry));
	if (!entry)
		return (false);
	entry->id = strs[0][0];
	entry->value = ft_strtrim(strs[1], "\n");
	if (!entry->value || !entry->value[0])
	{
		ump_clear(entry);
		return (false);
	}
	clear_array((void **)strs);
	ft_lstadd_back(&mapscan->textures, ft_lstnew(entry));
	return (true);
}

bool	rdr_readsurfs(t_mapscan *mapscan, char *line)
{		
	if (!line || (ft_strncmp(line, "F ", 2) && ft_strncmp(line, "C ", 2)))
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

