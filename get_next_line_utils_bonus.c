/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:25:38 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/02 03:50:55 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_memcpy(void *dest, const void *src)
{
	size_t	i;

	if ((!(src)) && (!(dest)))
		return ;
	i = 0;
	while (((const char *)src)[i])
		((unsigned char *) dest)[i++] = ((unsigned char *) src)[i];
}
