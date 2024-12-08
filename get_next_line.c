/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:16 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/08 18:39:49 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_nl_idx(char *string)
{
	long long	index;
	long long	i;

	index = -1;
	i = 0;
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
	long long		nl_idx;

	while (1)
	{
		if ((tfd->filld_size + BUFFER_SIZE) > (tfd->cont_max_sz_bytes - 1))
			if (alloc_more(tfd))
				return (NULL);
		bytes_read = read(tfd->fd_nbr, \
			&((tfd->content)[tfd->filld_size]), BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		tfd->filld_size += bytes_read;
		(tfd->content)[tfd->filld_size] = '\0';
		nl_idx = get_nl_idx(tfd->content);
		if ((bytes_read == 0) && (nl_idx == -1) && (tfd->filld_size > 0))
			return (modified_ft_strdup(tfd));
		if ((tfd->filld_size > 0) && (nl_idx != -1))
			return (extract_string(tfd, nl_idx));
		if (tfd->filld_size == 0 && nl_idx == -1)
			return (NULL);
	}
}

t_fd	*create_tfd(int fd)
{
	t_fd	*i_tfd;

	i_tfd = (t_fd *) malloc(sizeof(t_fd));
	if (!(i_tfd))
		return (NULL);
	i_tfd->cont_max_sz_bytes = (BUFFER_SIZE + 1);
	i_tfd->content = (char *) malloc(i_tfd->cont_max_sz_bytes);
	if (!(i_tfd->content))
	{
		free(i_tfd);
		return (NULL);
	}
	i_tfd->content[0] = '\0';
	i_tfd->filld_size = 0;
	i_tfd->fd_nbr = fd;
	i_tfd->next_tfd = NULL;
	return (i_tfd);
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
	i_tfd = create_tfd(fd);
	if (!(i_tfd))
		return (NULL);
	if (last_valid_tfd)
		last_valid_tfd->next_tfd = i_tfd;
	if (!(*tfd_head))
		*tfd_head = i_tfd;
	return (i_tfd);
}

char	*get_next_line(int fd)
{
	static t_fd		*head_tfd;
	t_fd			*curr_tfd;
	char			*result_string;

	if (fd < 0)
		return (NULL);
	curr_tfd = get_fd_ptr(fd, &head_tfd);
	if (!(head_tfd))
		head_tfd = curr_tfd;
	if (!(curr_tfd))
		return (NULL);
	result_string = get_string(curr_tfd);
	if (!(result_string))
		return (free_this_node(&head_tfd, curr_tfd));
	return (result_string);
}
