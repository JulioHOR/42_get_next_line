/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:25:38 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/05 02:59:55 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_memmove(unsigned char *dest, unsigned char *src)
{
	size_t	i;

	i = 0;
	if (dest > src)
	{
		while (src[i++]);
		while (&(src[i]) >= src)
		{
			dest[i] = src[i];
			i--;
		}
	}
	else
	{
		i = 0;
		while (((unsigned char *) src)[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = src[i];
	}
}

void	ft_memcpy(void *dest, const void *src, unsigned long max_i)
{
	size_t	i;

	if ((!(src)) && (!(dest)))
		return ;
	i = 0;
	if (max_i == 0)
	{
		while (((const char *)src)[i])
		{
			((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
			i++;
		}
		((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
	}
	else
	{
		while (i <= max_i)
		{
			((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
			i++;
		}
		((unsigned char *) dest)[++i] = '\0';
	}
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		string_len;
	char	*malloc_return;

	i = -1;
	while (s[++i]);
	string_len = i;
	malloc_return = (char *) malloc(string_len + 1);
	if (!malloc_return)
		return (NULL);
	i = 0;
	while (i < (string_len + 1))
	{
		malloc_return[i] = s[i];
		i++;
	}
	return (malloc_return);
}