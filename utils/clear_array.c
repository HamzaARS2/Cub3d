/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:00:03 by helarras          #+#    #+#             */
/*   Updated: 2024/12/04 16:03:54 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"


void	clear_array(void  **array)
{
	int i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i++] = NULL;
	}
	free(array);
}