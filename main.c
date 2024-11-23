/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:00 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/22 21:11:06 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

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