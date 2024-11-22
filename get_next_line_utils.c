/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:25:38 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/14 20:09:24 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_substring;
	size_t	s_len;
	size_t	real_substring_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (start >= s_len)
		return ((char *) malloc(1));
	real_substring_len = len;
	if (len > (s_len - start))
		real_substring_len = s_len - start;
	new_substring = (char *) malloc((real_substring_len + 1));
	if (!new_substring)
		return (((void *) 0));
	i = 0;
	while ((i < real_substring_len) && (s[start] != '\0'))
		new_substring[i++] = s[start++];
	new_substring[i] = '\0';
	return (new_substring);
}