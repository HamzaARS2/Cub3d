/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcontent_max.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:19:37 by helarras          #+#    #+#             */
/*   Updated: 2025/02/18 12:32:31 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstcontent_max(t_list *lst)
{
	int size;
	int current;
	
	size = 0;
	while (lst)
	{
		current = ft_strlen(lst->content);
		if (current > size)
			size = current;
		lst = lst->next;
	}
	return (size);
}
