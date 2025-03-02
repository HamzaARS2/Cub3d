/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:34:07 by helarras          #+#    #+#             */
/*   Updated: 2025/02/21 18:45:05 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan_bonus.h"

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
	k = 0;
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


bool	chk_position(char **map, t_point v2)
{
	if (v2.y == 0 || v2.x == 0 || !map[v2.y] || !map[v2.y + 1] || !map[v2.y - 1]
		|| !map[v2.y][v2.x + 1])
		return (mp_post_error(ERR_MAP_NOT_CLOSED));
	if (ft_strlen(map[v2.y - 1]) <= v2.x || !ump_is_mpcomponent(map[v2.y - 1][v2.x]))
		return (mp_post_error(ERR_MAP_NOT_CLOSED));
	if (ft_strlen(map[v2.y + 1]) <= v2.x || !ump_is_mpcomponent(map[v2.y + 1][v2.x]))
		return (mp_post_error(ERR_MAP_NOT_CLOSED));
	if (!ump_is_mpcomponent(map[v2.y][v2.x - 1]))
		return (mp_post_error(ERR_INVALID_CHAR));
	if (!ump_is_mpcomponent(map[v2.y][v2.x + 1]))
		return (mp_post_error(ERR_INVALID_CHAR));
	return (true);
}

// TODO: save start position!.
bool	chk_map(t_mapscan *mapscan)
{
	t_point v2;
	t_point start_pos;
	
	v2.y = 0;
	if (!chk_map_comp(mapscan->map))
		return (false);
	while (mapscan->map[v2.y])
	{
		v2.x = -1;
		if (!mapscan->map[v2.y][0])
			return (false);
		while (mapscan->map[v2.y][++v2.x])
		{
			if (ump_is_mpcomponent(mapscan->map[v2.y][v2.x]) && mapscan->map[v2.y][v2.x] != '1')
			{
				if (!chk_position(mapscan->map, v2))
					return (false);
				if (mapscan->map[v2.y][v2.x] != '0')
					mapscan->start_pos = (t_point) {v2.x, v2.y};
			}
		}
		v2.y++;
	}
	return (true);
}
