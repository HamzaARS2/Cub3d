/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:15:38 by helarras          #+#    #+#             */
/*   Updated: 2024/12/12 13:24:52 by helarras         ###   ########.fr       */
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
	while (line[i] && flag)
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

void	free_array(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	utl_charcount(char *str, int c)
{
	int i;
	int count;

	count = 0;
	i = 0;
	while (str && str[i])
		if (str[i++] == c)
			count++;
	return (count);
}