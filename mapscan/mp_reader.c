/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:23:16 by helarras          #+#    #+#             */
/*   Updated: 2024/11/28 13:37:01 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"

bool	rdr_readtex(t_mapscan *mapscan, char *line)
{
	t_entry	*entry;

	entry = malloc(sizeof(t_entry));
	if (!entry)
		return (false);
	if (!line  || (ft_strncmp(line, "NO", 2) && ft_strncmp(line, "SO", 2)
		&& ft_strncmp(line, "WE", 2) && ft_strncmp(line, "EA", 2)))
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

void	rdr_readmap(t_mapscan *mapscan, char *line)
{
	
}