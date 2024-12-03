/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:16 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/03 12:47:30 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_all_fd_nodes(t_fd **fd_head)
{
	t_fd		*i_node_fd;
	t_fd		*temp_ptr_fd;
	t_buffer	*i_node_buffer;
	t_buffer	*temp_ptr_buffer;

	i_node_fd = *fd_head;
	i_node_buffer = NULL;
	while (!(i_node_fd))
	{
		i_node_buffer = i_node_fd->head_tbuffer;
		while (i_node_buffer)
		{
			temp_ptr_buffer = i_node_buffer->next_tbuffer;
			free(i_node_buffer->buffer);
			i_node_buffer->buffer = NULL;
			free(i_node_buffer);
			i_node_buffer = temp_ptr_buffer;
		}
		temp_ptr_buffer = i_node_fd;
		i_node_fd = i_node_fd->next_tfd;
		free(temp_ptr_fd);
	}
}

char	*get_fd_ptr(int fd, t_fd **fd_head)
{
	t_fd	*i_fd_node;
	t_fd	*last_valid_node;

	last_valid_node = NULL;
	i_fd_node = *fd_head;
	while (i_fd_node)
	{
		if (i_fd_node->fd_nbr == fd)
			return (i_fd_node);
		last_valid_node = i_fd_node;
		i_fd_node = i_fd_node->next_tfd;
	}
	i_fd_node = (t_fd *) malloc(sizeof(t_fd));
	if (!(i_fd_node))
		return (NULL);
	i_fd_node->head_tbuffer = (t_buffer *) malloc(sizeof(t_buffer));
	if (!(i_fd_node->head_tbuffer))
	{
		free(i_fd_node);
		return (NULL);
	}
	i_fd_node->head_tbuffer->buffer = (char *) malloc(BUFFER_SIZE + 1);
	if (!(i_fd_node->head_tbuffer->buffer))
	{
		free_all_fd_nodes(i_fd_node);
		return (NULL);
	}
	i_fd_node->head_tbuffer->buffer[0] = '\0';
	i_fd_node->head_tbuffer->buffer[BUFFER_SIZE] = '\0';
	i_fd_node->last_tbuffer = i_fd_node->head_tbuffer;
	i_fd_node->fd_nbr = fd;
	i_fd_node->entire_len = 0;
	i_fd_node->next_tfd = NULL;
	if (!(*fd_head))
		*fd_head = i_fd_node;
	if (last_valid_node)
		last_valid_node->next_tfd = i_fd_node;
}

char	*concat_buffers(t_fd *fd_ptr)
{
	int				i;
	int				new_line_index;
	char			*result_string;
	t_buffer		*i_node_tbuffer;
	unsigned long	curr_pos;

	curr_pos = 0;
	new_line_index = -1;
	i = -1;
	while (fd_ptr->last_tbuffer->buffer[++i])
		if (fd_ptr->last_tbuffer->buffer[i] == '\n')
		{
			new_line_index = i;
			break ;
		}
	if ((new_line_index != -1) && (new_line_index != BUFFER_SIZE))
		fd_ptr->entire_len -= new_line_index;
	result_string = (char *) malloc((fd_ptr->entire_len + 1));
	if (!(result_string))
		return (NULL);
	i_node_tbuffer = fd_ptr->head_tbuffer;
	while (i_node_tbuffer)
	{
		i_node_tbuffer = fd_ptr->head_tbuffer;
		ft_memcpy(result_string, fd_ptr->last_tbuffer->buffer);
	}
	return (result_string);
}

char	*get_string(t_fd *fd_ptr)
{
	int			bytes_read;
	t_buffer	*latest_used_tbuffer;
	int			i;

	bytes_read = 0;
	while (1)
	{
		latest_used_tbuffer = fd_ptr->last_tbuffer;
		bytes_read = read(fd_ptr->fd_nbr, fd_ptr->last_tbuffer->buffer, \
			BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (fd_ptr->entire_len)
				return (concat_buffers(fd_ptr));
			return (NULL);
		}
		fd_ptr->last_tbuffer->buffer[bytes_read] = '\0';
		fd_ptr->entire_len += bytes_read;
		fd_ptr->last_tbuffer->next_tbuffer = (char *) malloc(BUFFER_SIZE + 1);
		if (!(fd_ptr->last_tbuffer->next_tbuffer))
			return (NULL);
		fd_ptr->last_tbuffer = fd_ptr->last_tbuffer->next_tbuffer;
		fd_ptr->last_tbuffer->buffer[0] = '\0';
		i = -1;
		while (latest_used_tbuffer->buffer[++i])
			if (latest_used_tbuffer->buffer[++i] == '\n')
			{
				if (i == 0)
				return (concat_buffers(fd_ptr));
			}
	}
}

char	*get_next_line(int fd)
{
	char		*result_string;
	static t_fd	*fd_head;

	if (fd < 0)
		return (NULL);
	fd_head = get_fd_ptr(fd, &fd_head);
	if (!(fd_head))
		return (NULL);
	result_string = NULL;
	result_string = get_string(fd_head);
	if (!(result_string))
	{
		free_all_fd_nodes(&fd_head);
		return (NULL);
	}
	return (result_string);
}
