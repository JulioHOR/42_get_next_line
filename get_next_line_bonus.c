/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:16 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/03 21:02:50 by juhenriq         ###   ########.fr       */
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

int	create_new_tbuffer_node(t_fd *fd_ptr)
{
	t_buffer	*created_tbuffer;
	t_buffer	*i_tbuffer;

	created_tbuffer = (t_buffer *) malloc(sizeof(t_buffer));
	if (!(created_tbuffer->next_tbuffer))
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
		if (create_new_tbuffer_node(fd_ptr))
		{
			free_all_fd_nodes(&fd_ptr);
			return (NULL);
		}
		fd_ptr->last_tbuffer->buffer[0] = '\0';
		// for debugging purposes
		unsigned long debug_variable_entire_len = debug_totalstrlen(fd_ptr);
		if (fd_ptr->entire_len != debug_variable_entire_len)
		{
			printf(
				"\n\nOpa! Temos incoerênica nos valores de debug!\nentire_len" \
				"é: %lu\nFunção de debug reportou: %lu\n\n", \
				fd_ptr->entire_len, debug_variable_entire_len);
		}
		// end of debugging code
		i = -1;
		while (latest_used_tbuffer->buffer[++i])
			if (latest_used_tbuffer->buffer[++i] == '\n')
			{
				if (i == 0)
				return (concat_buffers(fd_ptr));
			}
	}
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
