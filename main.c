/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:00 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/02 01:45:38 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

void	print_for_me(char *string)
{
	printf("%s", &string);
	fflush(stdout);
}

int	main(void)
{
	int		fd;
	char	*result_string;

	printf("\n\n--- Iniciando ---\n\n");
	fd = open("text_files/nossa poesia", O_RDONLY);
	if (!(fd))
	{
		printf("Não foi possível abrir o arquivo. Vamos encerrar o programa");
		return (0);
	}
	while (1)
	{
		result_string = get_next_line(fd);
		if (!(result_string))
		{
			printf("Chegamos ao fim do arquivo ou tivemos um erro.");
			return (0);
		}
		print_for_me(result_string);
		free(result_string);
	}
	printf("\n\n--- Encerrando ---\n\n");
	return (0);
}