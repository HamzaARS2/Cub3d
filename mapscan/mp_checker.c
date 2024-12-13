/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:34:07 by helarras          #+#    #+#             */
/*   Updated: 2024/12/13 18:26:37 by helarras         ###   ########.fr       */
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
			break;
	}
	ft_clear_array(rgb);
	k = ft_charcount(color, ',');
	return (i == 3 && k == 2);
}

// Checks for invalid component.
// Checks for duplicate/not exist player position.
static bool	chk_map_comp(char **map)
{
	int y;
	int x;
	int count;

	y = 0;
	count = 0;
	while (map[y] && count <= 1)
	{
		x = -1;
		while (map[y][++x])
		{
			if (!ft_iswhitespace(map[y][x]) && !ump_is_mpcomponent(map[y][x]))
				return (false);
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
					count++;
		}
		y++;
	}
	if (count == 0 || count > 1)
		return (false);
	return (true);
}


bool	chk_position(char **map, int x, int y)
{
	if (y == 0 || x == 0 || !map[y] || !map[y + 1] || !map[y - 1]
		|| !map[y][x + 1])
		return (false);
	if (ft_strlen(map[y - 1]) <= x || !ump_is_mpcomponent(map[y - 1][x]))
		return (false);
	if (ft_strlen(map[y + 1]) <= x || !ump_is_mpcomponent(map[y + 1][x]))
		return (false);
	if (!ump_is_mpcomponent(map[y][x - 1]))
		return (false);
	if (!ump_is_mpcomponent(map[y][x + 1]))
		return (false);
	return (true);
}

bool	chk_map(char **map)
{
	int y;
	int x;

	if (!chk_map_comp(map))
		return (false);
	y = 0;
	while (map[y])
	{
		x = -1;
		if (!map[y][0])
			return (false);
		while (map[y][++x])
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
				if (!chk_position(map, x, y))
					return (false);
		}
		y++;
	}
	return (true);
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