/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:24:16 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/14 20:08:51 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>

typedef struct	s_line
{
	char	*content;
	t_line	*next_line;
}	t_line;

char	*get_next_line(int fd)
{
	int		bytes_read;
	char	*buffer[BUFFER_SIZE];

	bytes_read = read(fd, buffer, BUFFER_SIZE);
}


#include <unistd.h>
#include <stdio.h>
void main_print_it_for_me(char *str)
{
	int	new_line_found;
	int	i;

	new_line_found = 0;
	int	i = -1;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			new_line_found = 1;
			break ;
		}
	}
	write(1, &(str[i]), i);
}

int	main(void)
{
	int		fd;
	char	*result;
	
	printf("\n\n--- Iniciando ---\n\n");

	fd = open("our text.txt", O_RDONLY);
	result = get_next_line(fd);
	
	main_print_it_for_me(result);
	free_it_for_me

	printf("\n\n--- Encerrando ---\n\n");
	return (0);
}
