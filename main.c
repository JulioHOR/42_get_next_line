/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:00 by juhenriq          #+#    #+#             */
/*   Updated: 2024/12/06 20:07:16 by juhenriq         ###   ########.fr       */
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
	int		fd_1;
	int		fd_2;
	int		execution_counter;
	char	*result_string;

	printf("\n\n--- Iniciando ---\n\n");
	if (0)
	{
		fd_1 = open("text_files/multiple_nl.txt", O_RDONLY);
		if (!(fd_1))
		{
			printf("Não foi possível abrir o arquivo. Vamos encerrar o programa");
			return (0);
		}
		while (1)
		{
			result_string = get_next_line(fd_1);
			if (!(result_string))
			{
				printf("< Teste 1: Chegamos ao fim do arquivo ou tivemos um erro. >");
				return (0);
			}
			print_for_me(result_string);
			free(result_string);
		}
	}
	if (0)
	{
		fd_1 = open("text_files/poesia.txt", O_RDONLY);
		if (!(fd_1))
		{
			printf("Não foi possível abrir o arquivo. Vamos encerrar o programa");
			return (0);
		}
		int	control = 0;
		while (1)
		{
			result_string = get_next_line(fd_1);
			if (!(control))
				close(fd_1);
			control++;
			if (control == 2)
				fd_1 = open("text_files/poesia.txt", O_RDONLY);
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
	if (1)
	{
		int	curr_fd;
		fd_1 = open("text_files/read_error.txt", O_RDONLY);
		fd_2 = open("text_files/lines_around_10.txt", O_RDONLY);
		execution_counter = 1;
		while (execution_counter <= 14)
		{
			if ((execution_counter == 1) || (execution_counter == 3) || \
				(execution_counter == 5) || (execution_counter == 7) || \
				(execution_counter == 9) || (execution_counter == 10) || \
				(execution_counter == 13) || (execution_counter == 14))
				curr_fd = fd_1;
			else
				curr_fd = fd_2;
			if (execution_counter == 7)
			{
				fd_1 = open("text_files/read_error.txt", O_RDONLY);
				curr_fd = fd_1;
			}
			result_string = get_next_line(curr_fd);
			if (execution_counter == 5)
			{
				printf("\n\nResult string deveria ser: NULL\n" \
					"Ela é:                     %s\n\n", result_string);
			}
			if (!(result_string) && (execution_counter == 4))
			{
				if (BUFFER_SIZE > 100)
				{
					do
					{
						result_string = get_next_line(fd_1);
						free(result_string);
					} while (result_string != NULL);
				}
				close(fd_1);
			}
			if (!(result_string))
			{
				printf("< Teste 1: Chegamos ao fim do arquivo ou tivemos um erro. >");
				fflush(stdout);
				return (0);
			}
			print_for_me(result_string);
			free(result_string);
			execution_counter++;
		}
	}
	printf("\n\n--- Encerrando ---\n\n");
	return (0);
}
