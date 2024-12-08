/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:25:38 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/07 23:22:53 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_memmove(unsigned char *dest, unsigned char *src)
{
	size_t	i;

	i = 0;
	if (dest > src)
	{
		while (src[i])
			i++;
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

char	*modified_ft_strdup(t_fd *tfd)
{
	int		i;
	int		string_len;
	char	*s;
	char	*malloc_return;

	s = tfd->content;
	i = 0;
	while (s[i])
		i++;
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
	tfd->filld_size = 0;
	return (malloc_return);
}

int	alloc_more(t_fd *curr_tfd)
{
	char			*new_string;
	unsigned long	new_size;
	unsigned long	i;

	new_size = ((curr_tfd->cont_max_sz_bytes - 1) * 2) + 1;
	if (new_size <= BUFFER_SIZE)
		new_size = (BUFFER_SIZE + 1);
	new_string = (char *) malloc((new_size));
	if (!(new_string))
		return (-1);
	curr_tfd->cont_max_sz_bytes = new_size;
	if ((!(new_string)) && (!(curr_tfd->content)))
		return (-1);
	i = 0;
	while (i <= curr_tfd->filld_size)
	{
		((unsigned char *) new_string)[i] = \
			((unsigned char *) curr_tfd->content)[i];
		i++;
	}
	((unsigned char *) new_string)[i] = '\0';
	free(curr_tfd->content);
	curr_tfd->content = new_string;
	return (0);
}

char	*extract_string(t_fd *tfd, long long nl_idx)
{
	char		*result_string;
	long long	i;

	result_string = (char *) malloc(nl_idx + 2);
	if (!(result_string))
		return (NULL);
	if ((!(tfd->content)) && (!(result_string)))
		return (NULL);
	i = 0;
	while (i <= nl_idx)
	{
		((unsigned char *) result_string)[i] = \
			((unsigned char *) tfd->content)[i];
		i++;
	}
	((unsigned char *) result_string)[i] = '\0';
	ft_memmove((unsigned char *) tfd->content, \
		(unsigned char *) &((tfd->content)[nl_idx + 1]));
	tfd->filld_size = (tfd->filld_size - nl_idx) - 1;
	return (result_string);
}
