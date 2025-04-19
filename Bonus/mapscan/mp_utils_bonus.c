/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:15:38 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 12:34:35 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan_bonus.h"

void	ump_clear(void *content)
{
	t_entry	*entry;

	if (!content)
		return ;
	entry = (t_entry *)content;
	free(entry->value);
	entry->value = NULL;
	free(content);
	entry = NULL;
}

bool	ump_is_empty_line(char *line)
{
	int		i;
	bool	flag;

	i = 0;
	flag = true;
	while (line && line[i] && flag)
	{
		if (ft_isprint(line[i]) && line[i] != 32)
			flag = false;
		i++;
	}
	return (flag);
}

char	**ump_create_map(t_list *maplst, t_point mapsize)
{
	int		i;
	char	**map;
	t_list	*current;

	if (!maplst)
		return (NULL);
	i = 0;
	current = maplst;
	map = malloc((mapsize.y + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	while (i < mapsize.y && current)
	{
		map[i] = ft_calloc(mapsize.x + 1, sizeof(char));
		ft_strlcpy(map[i++], (char *)current->content, mapsize.x + 1);
		current = current->next;
	}
	map[i] = NULL;
	ft_lstclear(&maplst, free);
	return (map);
}

bool	ump_is_mpcomponent(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D');
}

bool	ump_color_toint(char *color_str, char **rgb, int *color)
{
	int	r;
	int	g;
	int	b;

	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		ft_clear_array((void **)rgb);
		return (false);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_clear_array((void **)rgb);
	if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
		return (false);
	if (ft_charcount(color_str, ',') != 2)
		return (false);
	*color = get_rgba(r, g, b, 255);
	return (true);
}
