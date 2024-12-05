/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:16 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/05 04:00:01 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
// APAGUE ESSE INCLUDE!!!
#include <stdio.h>

void	*free_all_fd_nodes(t_fd **tfd_head)
{
	t_fd	*i_tfd;
	t_fd	*temp_tfd;

	write(1, "entrei", 6);
	if (!(*tfd_head))
		return (NULL);
	i_tfd = *tfd_head;
	while (i_tfd)
	{
		temp_tfd = i_tfd;
		free(i_tfd->content);
		i_tfd = i_tfd->next_tfd;
		free(temp_tfd);
	}
	*tfd_head = NULL;
	tfd_head = NULL;
	return (NULL);
}

int	alloc_more(t_fd *curr_tfd)
{
	char			*new_string;
	unsigned long	new_size;

	new_size = ((curr_tfd->cont_max_sz_bytes - 1) * 2) + 1;
	if (new_size <= BUFFER_SIZE)
		new_size = (BUFFER_SIZE + 1);
	new_string = (char *) malloc((new_size));
	if (!(new_string))
		return (-1);
	curr_tfd->cont_max_sz_bytes = new_size;
	ft_memcpy(new_string, curr_tfd->content, 0);
	free(curr_tfd->content);
	curr_tfd->content = new_string;
	return (0);
}

int	get_nl_idx(char *string, unsigned long filld_size, int bytes_read)
{
	long long	index;
	long long	i;

	index = -1;
	i = (filld_size - bytes_read);
	while (string[i])
	{
		if (string[i] == '\n')
		{
			index = i;
			break ;
		}
		i++;
	}
	return (index);
}

char	*get_string(t_fd *tfd)
{
	int				bytes_read;
	char			*result_string;
	long long		nl_idx;

	while (1)
	{
		result_string = NULL;
		if ((tfd->filld_size + BUFFER_SIZE) > (tfd->cont_max_sz_bytes - 1))
			if (alloc_more(tfd))
				return ((char *)free_all_fd_nodes);
		bytes_read = 0;
		bytes_read = read(tfd->fd_nbr, \
			&((tfd->content)[tfd->filld_size]), BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (tfd->filld_size)
			{
				result_string = ft_strdup(tfd->content);
				tfd->filld_size = 0;
				(tfd->content)[0] = '\0';
			}
			return (result_string);
		}
		tfd->filld_size += bytes_read;
		(tfd->content)[tfd->filld_size] = '\0';
		nl_idx = get_nl_idx(tfd->content, tfd->filld_size, bytes_read);
		if (nl_idx != -1)
		{
			result_string = (char *) malloc(nl_idx + 2);
			if (!(result_string))
				return (NULL);
			ft_memcpy(result_string, tfd->content, nl_idx);
			ft_memmove((unsigned char *) tfd->content, (unsigned char *) &((tfd->content)[nl_idx + 1]));
			tfd->filld_size = (tfd->filld_size - nl_idx) - 1;
			return (result_string);
		}
	}

}

t_fd	*get_fd_ptr(int fd, t_fd **tfd_head)
{
	t_fd	*i_tfd;
	t_fd	*last_valid_tfd;

	last_valid_tfd = NULL;
	i_tfd = *tfd_head;
	while (i_tfd)
	{
		if (i_tfd->fd_nbr == fd)
			return (i_tfd);
		last_valid_tfd = i_tfd;
		i_tfd = i_tfd->next_tfd;
	}
	i_tfd = (t_fd *) malloc(sizeof(t_fd));
	if (!(i_tfd))
		return (NULL);
	i_tfd->cont_max_sz_bytes = INITIAL_CONTENT_SIZE;
	i_tfd->content = (char *) malloc(i_tfd->cont_max_sz_bytes);
	if (!(i_tfd->content))
	{
		free(i_tfd);
		return (NULL);
	}
	i_tfd->content[0] = '\0';
	i_tfd->filld_size = 0;
	i_tfd->fd_nbr = fd;
	if (last_valid_tfd)
		last_valid_tfd->next_tfd = i_tfd;
	return (i_tfd);
}

char	*get_next_line(int fd)
{
	char		*result_string;
	static t_fd	*curr_tfd;

	if (fd < 0)
		return (NULL);
	curr_tfd = get_fd_ptr(fd, &curr_tfd);
	if (!(curr_tfd))
		return (NULL);
	result_string = get_string(curr_tfd);
	if (!(result_string))
		return (free_all_fd_nodes(&curr_tfd));
	return (result_string);
}
