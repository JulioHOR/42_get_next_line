/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:25:38 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/04 02:34:20 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_memcpy(void *dest, const void *src, unsigned long *i)
{
	size_t j;

	if ((!(src)) && (!(dest)))
		return ;
	j = 0;
	while (((const char *)src)[j])
	{
		((unsigned char *) dest)[*i] = ((unsigned char *) src)[*i];
		*i++;
	}
	((unsigned char *) dest)[*i] = ((unsigned char *) src)[*i];
}
