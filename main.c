/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:00 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/06 00:19:04 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

void	*mock_malloc(size_t size)
{
	static int	malloc_attempt;
	int			force_failure_attempt;
	void		*return_ptr;

	// write (1, "entramos", 8);
	malloc_attempt++;
	force_failure_attempt = 4;
	if (malloc_attempt == force_failure_attempt)
	{
		write (1, "tentativa falha", 15);
		return (NULL);
	}
	#undef malloc
	extern void *malloc(size_t);
	return_ptr = malloc(size);
	#define malloc(size) mock_malloc(size);
	return (return_ptr);
}

void	print_for_me(char *string)
{
	if (!(string))
		return ;
	printf("%s", string);
	fflush(stdout);
}

int	main(void)
{
	int		fd;
	char	*result_string;

	printf("\n\n--- Iniciando ---\n\n");
	if (0)
	{
		fd = open("text_files/multiple_nl.txt", O_RDONLY);
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
				printf("< Teste 1: Chegamos ao fim do arquivo ou tivemos um erro. >");
				return (0);
			}
			print_for_me(result_string);
			free(result_string);
		}
	}
	if (1)
	{
		fd = open("text_files/poesia.txt", O_RDONLY);
		if (!(fd))
		{
			printf("Não foi possível abrir o arquivo. Vamos encerrar o programa");
			return (0);
		}
		int	control = 0;
		while (1)
		{
			result_string = get_next_line(fd);
			if (!(control))
				close(fd);
			control++;
			if (control == 2)
				fd = open("text_files/poesia.txt", O_RDONLY);
			if (!(result_string) && control >= 4)
			{
				printf("< Teste 1: Chegamos ao fim do arquivo ou tivemos um erro. >");
				fflush(stdout);
				return (0);
			}
			print_for_me(result_string);
			free(result_string);
		}
	}
	printf("\n\n--- Encerrando ---\n\n");
	return (0);
}
