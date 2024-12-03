/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:41 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/03 12:47:30 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

#include <stdlib.h>
#include <unistd.h>

typedef struct s_buffer
{
	char			*buffer;
	struct s_buffer	*next_tbuffer;
}	t_buffer;

typedef struct s_fd
{
	int				fd_nbr;
	unsigned long	entire_len;
	t_buffer		*head_tbuffer;
	t_buffer		*last_tbuffer;
	struct s_fd		*next_tfd;
}	t_fd;

char	*get_next_line(int fd);
void	ft_memcpy(void *dest, const void *src);

#endif
