/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:16 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/22 21:15:03 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*prepare_str_for_return(char *buffer)
{
	int		i;
	int		new_line_found;
	char	*str_for_return;
	char	*old_buffer_content;

	new_line_found = 0;
	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == '\n')
		{
			new_line_found = 1;
			break ;
		}
	}
	if (new_line_found)
	{
		str_for_return = ft_substr(buffer, 0, i);
		old_buffer_content = buffer;
		buffer = ft_substr(buffer, (i + 1), BUFFER_SIZE);
		free(old_buffer_content);
		return (str_for_return);
	}
	return (buffer);
}

locate_fd

char	*get_next_line(int fd)
{
	int				bytes_read;
	static t_fds	*fds;

	if (!(buffer))
	{
		buffer = (char *) malloc(BUFFER_SIZE);
		if (!(buffer))
			return (NULL);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (NULL);
	if (bytes_read == 0 && )
	return (prepare_str_for_return(buffer));
}
