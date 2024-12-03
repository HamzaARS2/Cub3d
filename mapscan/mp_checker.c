/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:34:07 by helarras          #+#    #+#             */
/*   Updated: 2024/12/03 14:01:36 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"


bool	chk_format(char *mapfile)
{
	
}

t_mperror	chk_textures(t_list *textures)
{
	t_list		*current;
	t_entry		*entry;
	
	if (!textures)
		return (ERR_MISSING_TEXTURE);
	
	current = textures;
	while (current)
	{
		entry = (t_entry *) current->content;
		if (entry->id)
		current = current->next;
	}
}