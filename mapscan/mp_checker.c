/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:34:07 by helarras          #+#    #+#             */
/*   Updated: 2024/12/17 12:00:52 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"

bool	chk_format(char *mapfile)
{
	char *ext;
	
	if (!mapfile || mapfile[0] == 0)
		return (mp_post_error(ERR_FILE_READ));
	ext = ft_strnstr(mapfile, ".cub", ft_strlen(mapfile));
	if (!(ext && ext[4] == 0))
		return (mp_post_error(ERR_FILE_FORMAT));	
	return (true);
}



bool	chk_color(char *color_str, int *color)
{
	char	**rgb;
	int i;
	int k;
	int d;
	
	i = 0;
	rgb = ft_split(color_str, ',');
	while (rgb && rgb[i] && k >= 0)
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
			k = -1;
	}
	if (!ump_color_toint(color_str, rgb, color))
		return (false);		
	return (i == 3 && k >= 0);
}

// Checks for invalid component.
// Checks for duplicate/not exist player position.
static t_mperror	chk_map_comp(char **map)
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
				return (mp_post_error(ERR_INVALID_CHAR));
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
					count++;
		}
		y++;
	}
	if (count > 1)
		return (mp_post_error(ERR_MULTIPLE_START));
	else if (count == 0)
		return (mp_post_error(ERR_NO_START));
	return (true);
}


bool	chk_position(char **map, int x, int y)
{
	if (y == 0 || x == 0 || !map[y] || !map[y + 1] || !map[y - 1]
		|| !map[y][x + 1])
		return (mp_post_error(ERR_MAP_NOT_CLOSED));
	if (ft_strlen(map[y - 1]) <= x || !ump_is_mpcomponent(map[y - 1][x]))
		return (mp_post_error(ERR_MAP_NOT_CLOSED));
	if (ft_strlen(map[y + 1]) <= x || !ump_is_mpcomponent(map[y + 1][x]))
		return (mp_post_error(ERR_MAP_NOT_CLOSED));
	if (!ump_is_mpcomponent(map[y][x - 1]))
		return (mp_post_error(ERR_INVALID_CHAR));
	if (!ump_is_mpcomponent(map[y][x + 1]))
		return (mp_post_error(ERR_INVALID_CHAR));
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
