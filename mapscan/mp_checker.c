/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mp_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:34:07 by helarras          #+#    #+#             */
/*   Updated: 2024/12/08 13:32:14 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mapscan.h"
// N(78) + S(83) + W(87) + E(69)  = 317

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

// t_mperror	chk_textures(t_list *textures)
// {
// 	t_list		*current;
// 	t_entry		*entry;
// 	int			ids_sum;
	
// 	if (!textures)
// 		return (ERR_MISSING_TEXTURE);
// 	ids_sum = 0;
// 	current = textures;
// 	while (current)
// 	{
// 		entry = (t_entry *) current->content;
// 		ids_sum += entry->id;
// 		if (!entry->value)
// 			return (ERR_MISSING_TEXTURE);
// 		current = current->next;
// 	}
// 	if (ids_sum != 317)
// 		return (ERR_DUPLICATED_TEXTURE);
// 	return (NO_ERROR);
// }