/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:41 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/07 23:06:14 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
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
void	ft_memmove(unsigned char *dest, unsigned char *src);
int		alloc_more(t_fd *curr_tfd);
char	*modified_ft_strdup(t_fd *tfd);
char	*extract_string(t_fd *tfd, long long nl_idx);

#endif
