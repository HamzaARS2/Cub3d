/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:34:07 by helarras          #+#    #+#             */
/*   Updated: 2024/12/12 14:59:34 by helarras         ###   ########.fr       */
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
	char	**rgb;
	int i;
	int k;
	int d;
	
	i = 0;
	rgb = ft_split(color, ',');
	while (rgb && rgb[i])
	{
		k = 0;
		d = 0;
		while (rgb[i][k] == 32)
			k++;
		while (ft_isdigit(rgb[i][k]) && ++d)
			k++;
		while (rgb[i][k] == 32)
			k++;
		if (rgb[i++][k] || d == 0)
			return (false);
	}
	free_array(rgb);
	k = utl_charcount(color, ',');
	return (i == 3 && k == 2);
}


// bool	chk_map(char **map)
// {
// 	int y;
// 	int x;

// 	y = 0;
// 	while (map[y])
// 	{
// 		x = 0;
// 		if (map[y][0] == '\n')
// 			return (false);
// 		while (map[y][x])
// 		{
			
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (true);
// }

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