/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:16 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/04 02:39:44 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
// APAGUE ESSE INCLUDE
#include <stdio.h>

void	free_all_fd_nodes(t_fd **fd_head)
{
	t_fd		*i_node_tfd;
	t_fd		*temp_ptr_tfd;
	t_buffer	*i_node_tbuffer;
	t_buffer	*temp_ptr_tbuffer;

	if (!(*fd_head))
		return ;
	i_node_tfd = *fd_head;
	i_node_tbuffer = NULL;
	while (!(i_node_tfd))
	{
		i_node_tbuffer = i_node_tfd->head_tbuffer;
		while (i_node_tbuffer)
		{
			temp_ptr_tbuffer = i_node_tbuffer->next_tbuffer;
			free(i_node_tbuffer->buffer);
			i_node_tbuffer->buffer = NULL;
			free(i_node_tbuffer);
			i_node_tbuffer = temp_ptr_tbuffer;
		}
		temp_ptr_tfd = i_node_tfd;
		i_node_tfd = i_node_tfd->next_tfd;
		free(temp_ptr_tfd);
	}
}

unsigned long	debug_totalstrlen(t_fd *head_tfd)
{
	unsigned long	i;
	t_buffer		*i_tbuffer;

	write(1, "oi", 2);
	i_tbuffer = head_tfd->head_tbuffer;
	i = 0;
	while (i_tbuffer)
	{
		while (i_tbuffer->buffer[i])
			i++;
		i_tbuffer = i_tbuffer->next_tbuffer;
	}
	return (i);
}

char	*concat_buffers(t_fd *fd_ptr)
{
	int				new_line_index;
	char			*result_string;
	t_buffer		*i_node_tbuffer;
	unsigned long	curr_pos;

	return (result_string);
}

int	create_new_tbuffer_node(t_fd *fd_ptr)
{
	t_buffer	*created_tbuffer;
	t_buffer	*i_tbuffer;

	created_tbuffer = (t_buffer *) malloc(sizeof(t_buffer));
	if (!(created_tbuffer))
		return (1);
	created_tbuffer->buffer = (char *) malloc(BUFFER_SIZE + 1);
	if (!(created_tbuffer->buffer))
		return (1);
	created_tbuffer->buffer[0] = '\0';
	created_tbuffer->buffer[BUFFER_SIZE] = '\0';
	created_tbuffer->next_tbuffer = NULL;
	if (!(fd_ptr->head_tbuffer))
		fd_ptr->head_tbuffer = created_tbuffer;
	if(fd_ptr->last_tbuffer)
		fd_ptr->last_tbuffer->next_tbuffer = created_tbuffer;
	fd_ptr->last_tbuffer = created_tbuffer;
	return (0);
}

char	*get_string(t_fd *fd_ptr)
{
	int			bytes_read;

	bytes_read = 0;
	return (NULL);
}

t_fd	*get_fd_ptr(int fd, t_fd **fd_head)
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
	*fd_head = i_fd_node;
	if (create_new_tbuffer_node(*fd_head))
	{
		free_all_fd_nodes(fd_head);
		return (NULL);
	}
	if (!(*fd_head))
		*fd_head = i_fd_node;
	if (last_valid_node)
		last_valid_node->next_tfd = i_fd_node;
	return (i_fd_node);
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
