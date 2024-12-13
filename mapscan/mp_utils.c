/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:15:38 by helarras          #+#    #+#             */
/*   Updated: 2024/12/13 11:27:00 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"

void	ump_clear(void *content)
{
	t_entry *entry;

	if (!content)
		return ;
	entry = (t_entry *) content;
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

char	**ump_create_map(t_list *maplst, int mapsize)
{
	int		i;
	char	**map;
	t_list	*current;
	
	if (!maplst)
		return (NULL);
	i = 0;
	current = maplst;
	map = malloc((mapsize + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	while (i < mapsize && current)
	{
		map[i++] = (char *)current->content;
		current = current->next;
	}
	map[i] = NULL;
	ft_lstclear(&maplst, NULL);
	return (map);
}

bool	ump_is_mpcomponent(char c)
{
	return (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

void	ump_post_error(t_mperror error)
{
	if (error == ERR_INVALID_DATA)
		ft_putstr_fd("Error\nInvalid data!.\n", 2);
	else if (error == ERR_MISSING_DATA)
		ft_putstr_fd("Error\nMissing data!.\n", 2);
	else if (error == ERR_DUPLICATED_DATA)
		ft_putstr_fd("Error\nDuplicated data!.\n", 2);
	else if (error == ERR_MAP_NOT_FOUND)
		ft_putstr_fd("Error\nMap not found!.\n", 2);
	else if (error == ERR_FILE_FORMAT)
		ft_putstr_fd("Error\nWrong file format!.\n", 2);
	else if (error == ERR_FILE_READ)
		ft_putstr_fd("Error\nCan't read file!.\n", 2);
	else if (error == ERR_INVALID_COLOR)
		ft_putstr_fd("Error\nInvalid color!.\n", 2);
	else if (error == ERR_INVALID_MAP)
		ft_putstr_fd("Error\nInvalid map!.\n", 2);

}