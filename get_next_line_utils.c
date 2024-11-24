/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:25:38 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/24 01:28:07 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!(s))
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	arr_len;

	arr_len = 0;
	while (src[arr_len] != '\0')
		arr_len++;
	if (size <= 0)
		return (arr_len);
	i = 0;
	while (src[i] != '\0' && (i < (size - 1)))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (arr_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_size;
	size_t	dst_size;
	size_t	actual_amount_of_bytes_to_cpy;

	src_size = ft_strlen(src);
	dst_size = ft_strlen(dst);
	if (size <= dst_size)
		return (src_size + size);
	actual_amount_of_bytes_to_cpy = (size - dst_size - 1);
	i = dst_size;
	j = 0;
	while ((j < actual_amount_of_bytes_to_cpy) && (src[j] != '\0'))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (src_size + dst_size);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	int		combined_len;
	char	*new_string;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	combined_len = (s1_len + s2_len) + 1;
	new_string = (char *) malloc(combined_len);
	if (!(new_string))
		return ((void *) 0);
	ft_strlcpy(new_string, s1, s1_len + 1);
	ft_strlcat(new_string, s2, combined_len);
	return (new_string);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_substring;
	size_t	s_len;
	size_t	real_substring_len;
	size_t	i;

	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		new_substring = (char *) malloc(1);
		if (!(new_substring))
			return (NULL);
		new_substring[0] = '\0';
		return (new_substring);
	}
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

char	*ft_strdup(const char *s)
{
	int		i;
	int		string_len;
	char	*malloc_return;

	string_len = ft_strlen(s);
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
