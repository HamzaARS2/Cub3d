/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:34:07 by helarras          #+#    #+#             */
/*   Updated: 2024/12/09 12:01:26 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"

bool	chk_format(char *mapfile)
{
	char *ext;
	
	if (!mapfile || mapfile[0] == 0)
		return (false);
	ext = ft_strnstr(mapfile, ".cub", ft_strlen(mapfile));
	if (!(ext && ext[4] == 0))
		return (false);	
	return (true);
}

bool	chk_color(char *color)
{
	int i;
	t_mperror error;
	
	i = 0;
	error = NO_ERROR;
	while (color[i] && !error)
	{
		if (!ft_isdigit(color[i]))
		{
			if (i == 0  || color[i] != ',' || color[i - 1] == ',')
				error = ERR_INVALID_COLOR;
		}
		i++;
	}
	mp_post_error(error);
	return (!error);
}

// bool	chk_color(char *fcolor)
// {
// 	int i;
// 	int byte;
// 	int rgba[4];

// 	i = 0;
// 	byte = 0;
// 	while (fcolor[i])
// 	{
// 		if (ft_isdigit(fcolor[i]))
// 		{
// 			rgba[byte] = (rgba[byte] * 10) + fcolor[i] - 48;
// 		}
// 		else if (i > 0 && fcolor[i] == ',' && fcolor[i - 1] != ',')
// 		{
// 			rgba[byte] = rgba[byte] << 24 / byte;
// 			byte++;
// 		}
		
// 		i++;
// 	}
// }