/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:16 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/23 20:45:46 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> // REMOVA DEPOIS JESUS

int	debug_is_not_null_terminated(char *str)
{
	int i;

	i = -1;
	while (str[i] < 50)
		if (!(str[i]))
			return (0);
	return (1);
}

int	new_line_index(char *content)
{
	int	i;
	int	new_line_counter;

	new_line_counter = 0;
	i = -1;
	while (content[++i])
		if (content[i] == '\n')
			return (i);
	return (-1);
}

int	resets_fd(t_fd *fd_ptr, int what_to_free)
{
	if (what_to_free == 0)
	{
		free(fd_ptr->buffer);
		free(fd_ptr->content);
		fd_ptr->buffer = NULL;
		fd_ptr->content = NULL;
	}
	if (what_to_free == 1)
	{
		free(fd_ptr->buffer);
		fd_ptr->buffer = NULL;
	}
	if (what_to_free == 2)
	{
		free(fd_ptr->content);
		fd_ptr->content = NULL;
	}
	return (0);
}

char	*prepare_str_for_return(t_fd *fd_ptr)
{
	char	*str_to_return;
	char	*temp_char_ptr;
	int		bytes_read;
	int		i;
	char	*just_to_check;

	while (1)
	{
		// if buffer points to NULL, then we should return NULL
		if (fd_ptr->buffer == NULL)
			return (NULL);
		bytes_read = read(fd_ptr->fd_nbr, fd_ptr->buffer, BUFFER_SIZE);
		if ((fd_ptr->content == NULL) && (bytes_read == 0))
			return (NULL);
		// if (*(fd_ptr->content) == -66)
		// 	printf("bug vai ocorrer");
		if (bytes_read >= 0)
		{
			if (bytes_read != BUFFER_SIZE)
				fd_ptr->buffer[bytes_read] = '\0';
			fd_ptr->buffer[bytes_read] = '\0';
			if (fd_ptr->content)
			{
				temp_char_ptr = fd_ptr->content;
				if (bytes_read == 0)
				{
					str_to_return = ft_strdup(fd_ptr->content);
					resets_fd(fd_ptr, 0);
					return (str_to_return);
				}
				just_to_check = ft_substr(fd_ptr->buffer, 0, bytes_read);
				fd_ptr->content = ft_strjoin(fd_ptr->content, ft_substr(fd_ptr->buffer, 0, bytes_read));
				if (!(fd_ptr->content))
					return (NULL);
				free(temp_char_ptr);
				temp_char_ptr = NULL;
			}
			else
				fd_ptr->content = ft_strdup(fd_ptr->buffer);
		}
		i = new_line_index(fd_ptr->content);
		if (i != -1)
		{
			str_to_return = ft_substr(fd_ptr->content, 0, (i + 1));
			temp_char_ptr = fd_ptr->content;
			// se strlen = i, só limpe fd_ptr->content era bug aqui de acesso
			// ou seja, o final de content é uma nova linha.
			// if (ft_strlen(fd_ptr->content) == i + 1)
			// 	resets_fd(fd_ptr, 2);
			// else
			// {
			// 	fd_ptr->content = ft_substr(fd_ptr->content, (i + 1), (ft_strlen(fd_ptr->content) - i));
			// 	free(temp_char_ptr);
			// 	temp_char_ptr = NULL;
			// }
			fd_ptr->content = ft_substr(fd_ptr->content, (i + 1), (ft_strlen(fd_ptr->content) - i));
			free(temp_char_ptr);
			temp_char_ptr = NULL;
			// if there's a cathastrophical failure, free everything.
			if (!(fd_ptr->content))
			{
				resets_fd(fd_ptr, 0);
				return (NULL);
			}
			return (str_to_return);
		}
	}
}

t_fd	*get_fd_pointer(int desired_fd, t_fd *i_node)
{
	t_fd	*last_valid_node;

	last_valid_node = NULL;
	while (i_node)
	{
		if (i_node->fd_nbr == desired_fd)
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
	i_node->fd_nbr = desired_fd;
	i_node->content = NULL;
	i_node->next_node = NULL;
	return (i_node);
}

char	*get_next_line(int fd)
{
	static t_fd	*head_node;
	t_fd		*fd_ptr;

	if (!(head_node))
	{
		head_node = (t_fd *) malloc(sizeof(t_fd));
		if (!(head_node))
			return (NULL);
		head_node->buffer = (char *) malloc(BUFFER_SIZE + 1);
		if (!(head_node->buffer))
			return (NULL);
		head_node->buffer[BUFFER_SIZE] = '\0';
		head_node->fd_nbr = fd;
		head_node->content = NULL;
		head_node->next_node = NULL;
	}
	fd_ptr = get_fd_pointer(fd, head_node);
	if (!(fd_ptr))
		return (NULL);
	return (prepare_str_for_return(fd_ptr));
}
