/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helarras <helarras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:07:38 by helarras          #+#    #+#             */
/*   Updated: 2024/12/12 17:08:07 by helarras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charcount(char *str, int c)
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
