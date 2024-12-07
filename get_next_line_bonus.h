/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:41 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/07 18:35:22 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_fd
{
	int				fd_nbr;
	char			*content;
	unsigned long	cont_max_sz_bytes;
	unsigned long	filld_size;
	struct s_fd		*next_tfd;
}	t_fd;

char	*get_next_line(int fd);
void	ft_memcpy(void *dest, const void *src, unsigned long max_i);
void	ft_memmove(unsigned char *dest, unsigned char *src);
char	*ft_strdup(char *s);

#endif
