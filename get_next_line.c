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
#include <stdio.h>

char	*prepare_str_for_return(char *buffer)
{
	int		i;
	int		new_line_found;
	char	*str_for_return;
	char	*old_buffer_content;

	new_line_found = 0;
	i = -1;
	while (buffer[++i])
	{
		if (buffer[i] == '\n')
		{
			new_line_found = 1;
			break ;
		}
	}
	if (new_line_found)
	{
		str_for_return = ft_substr(buffer, 0, i);
		old_buffer_content = buffer;
		buffer = ft_substr(buffer, (i + 1), BUFFER_SIZE);
		free(old_buffer_content);
		return (str_for_return);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	int			bytes_read;
	static char	*buffer;

	if (!(buffer))
	{
		buffer = (char *) malloc(BUFFER_SIZE);
		if (!(buffer))
			return (NULL);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (NULL);
	if (bytes_read == 0 && )
	return (prepare_str_for_return(buffer));
}

void	main_print_it_for_me(char *str)
{
	int	new_line_found;
	int	i;

	new_line_found = 0;
	i = -1;
	if (!(str))
	{
		printf("Recebemos um ponteiro nulo, e portanto não pudemos " \
			"escrever nada.");
		return ;
	}
	printf("%s", str);
}

void	main_free_it_for_me(void **target_pointer)
{
	free(*target_pointer);
	*target_pointer = NULL;
}

int	main(void)
{
	int		fd;
	char	*result;

	printf("\n\n--- Iniciando ---\n\n");

	fd = open("our text.txt", O_RDONLY);
	if (!(fd))
	{
		printf("O arquivo não foi encontrado, então encerraremos por aqui.");
		printf("\n\n--- Encerrando ---\n\n");
		return (0);
	}
	while (1)
	{
		result = get_next_line(fd);
		if (!(result))
		{
			printf("\n\n< Fim! Acabamos de ler o arquivo, ou "
				"tivemos um erro. >");
			printf("\n\n--- Encerrando ---\n\n");
			return (0);
		}
		main_print_it_for_me(result);
	}
	main_free_it_for_me((void *)&result);
	printf("\n\n--- Encerrando ---\n\n");
	return (0);
}
