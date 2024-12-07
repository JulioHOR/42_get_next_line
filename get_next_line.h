
#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

// #  define	malloc(size) mock_malloc(size);

#include <stdlib.h>
#include <unistd.h>

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
char	*ft_strdup(const char *s);

#endif
