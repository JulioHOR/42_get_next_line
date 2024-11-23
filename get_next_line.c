/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:16 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/23 04:05:12 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	resets_fd(t_fd *fd_pointer, int what_to_free)
{
	if (what_to_free == 0)
	{
		free(fd_pointer->buffer);
		free(fd_pointer->content);
		fd_pointer->buffer = NULL;
		fd_pointer->content = NULL;
	}
	if (what_to_free == 1)
	{
		free(fd_pointer->buffer);
		fd_pointer->buffer = NULL;
	}
	if (what_to_free == 2)
	{
		free(fd_pointer->content);
		fd_pointer->content = NULL;
	}
}

char	*prepare_str_for_return(t_fd *fd_pointer)
{
	int		i;
	char	*str_to_return;
	char	*temp_char_ptr;
	int		bytes_read;

	while (1)
	{
		if (!(fd_pointer->buffer))
			return (NULL);
		bytes_read = read(fd_pointer->fd_number, fd_pointer->buffer, BUFFER_SIZE);
		if ((bytes_read <= 0) && (fd_pointer->content == NULL))
			return (NULL);
		if ((bytes_read == 0) && (fd_pointer->content))
		{
			str_to_return = ft_strdup(fd_pointer->content);
			resets_fd(fd_pointer, 0);
			return (str_to_return);
		}
		i = -1;
		while (fd_pointer->buffer[++i])
		{
			if (fd_pointer->buffer[++i] == '\n')
			{
				if (fd_pointer->content)
				{
					str_to_return = ft_strjoin(fd_pointer->content, \
						ft_substr(fd_pointer->buffer, 0, i));
					resets_fd()
				} else
				{
					if ((ft_strlen(fd_pointer->buffer) - 1) == i)
						str_to_return = ft_strdup(fd_pointer->buffer);
					else
					{
						str_to_return = ft_substr(fd_pointer->buffer, 0, i);
						fd_pointer->content = ft_substr(fd_pointer->buffer, i + 1, (ft_strlen(fd_pointer->buffer) - 1));
					}
				}
				break ;
			}
			temp_char_ptr = fd_pointer->content;
			fd_pointer->content = ft_strjoin(fd_pointer->content, fd_pointer->buffer);
			free(temp_char_ptr);
			temp_char_ptr = NULL;
			if (!(fd_pointer->content))
				return (NULL);
		}
		return (str_to_return);
	}
}

t_fd	*get_fd_pointer(int desired_fd, t_fd *i_node)
{
	t_fd	*last_valid_node;

	last_valid_node = NULL;
	while (i_node)
	{
		if (i_node->fd_number == desired_fd)
			return (i_node);
		last_valid_node = i_node;
		i_node = i_node->next_node;
	}
	last_valid_node->next_node = (t_fd *) malloc(sizeof(t_fd));
	if (!(last_valid_node->next_node))
			return (NULL);
	i_node = last_valid_node->next_node;
	i_node->buffer = (char *) malloc(BUFFER_SIZE);
	if (!(i_node->buffer))
		return (NULL);
	i_node->fd_number = desired_fd;
	i_node->content = NULL;
	i_node->next_node = NULL;
	return (i_node);
}

char	*get_next_line(int fd)
{
	static t_fd	*head_node;
	t_fd		*fd_pointer;

	if (!(head_node))
	{
		head_node = (t_fd *) malloc(sizeof(t_fd));
		if (!(head_node))
			return (NULL);
		head_node->buffer = (char *) malloc(BUFFER_SIZE);
		if (!(head_node->buffer))
			return (NULL);
		head_node->fd_number = fd;
		head_node->content = NULL;
		head_node->next_node = NULL;
	}
	fd_pointer = get_fd_pointer(fd, head_node);
	if (!(fd_pointer))
		return (NULL);
	return (prepare_str_for_return(fd_pointer));
}
