/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:02:57 by helarras          #+#    #+#             */
/*   Updated: 2025/04/19 11:03:12 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_array(void **array, int i)
{
	while (i >= 0 && array[i])
		free(array[i--]);
	free(array);
	return (NULL);
}
