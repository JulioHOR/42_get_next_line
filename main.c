/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhenriq <dev@juliohenrique.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 21:10:00 by juhenriq          #+#    #+#             */
/*   Updated: 2024/11/29 04:13:49 by juhenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	main_print_it_for_me(char *str)
{
	if (!(str))
	{
		printf("Recebemos um ponteiro nulo, e portanto não pudemos " \
			"escrever nada.");
		return ;
	}
	printf("%s", str);
	fflush(stdout);
}

void	main_free_it_for_me(void **target_pointer)
{
	free(*target_pointer);
	*target_pointer = NULL;
}

int	main(void)
{
	int		fd[2];
	char	*text_file_names[2];
	int		i;
	char	*result;
	int		numbers_of_calls;

	text_file_names[0] = "text_files/our text.txt";
	text_file_names[1] = "text_files/poesia.txt";

	printf("\n\n--- Iniciando ---\n\n");

	// 2 fd's tests
	if (0)
	{
		i = 0;
		while (i < 2)
		{
			fd[i] = open(text_file_names[i], O_RDONLY);
			if (!(fd[i++]))
			{
				printf("O arquivo não foi encontrado, então encerraremos por aqui.");
				printf("\n\n--- Encerrando ---\n\n");
				return (0);
			}
		}
		numbers_of_calls = 0;
		while (1)
		{
			result = get_next_line(fd[numbers_of_calls]);
			if (!(result))
			{
				printf("< Fim! Ou acabamos de ler o arquivo, ou "
					"tivemos um erro. >\n\n");
				numbers_of_calls++;
				if (numbers_of_calls == 2)
				{
					printf("\n\n--- Encerrando ---\n\n");
					return (0);
				}
				continue ;
			}
			main_print_it_for_me(result);
		}
		main_free_it_for_me((void *)&result);
	}

	if (0)
	{
		printf("\n\n--- Teste de fd inválido ---\n\n");
		int	invalid_fd = 123;
		while (1)
		{
			result = get_next_line(invalid_fd);
			if (!(result))
			{
				printf("< Fim! Ou acabamos de ler o arquivo, ou "
					"tivemos um erro. >\n\n");
				printf("\n\n--- Encerrando ---\n\n");
				return (0);
			}
			main_print_it_for_me(result);
		}
		main_free_it_for_me((void *)&result);
	}

	// teste do gpt 1
	if (0) // Altere para `if(0)` para desativar este bloco de testes
	{
		int fd_gpt;
		char *line;

		// Teste 1: Arquivo vazio
		printf("Teste 1: Arquivo vazio\n");
		fd_gpt = open("text_files/empty.txt", O_RDONLY);
		if (fd_gpt == -1) {
			perror("Erro ao abrir empty.txt");
		} else {
			line = get_next_line(fd_gpt);
			if (line == NULL) {
				printf("Linha correta: (NULL)\n");
			} else {
				printf("Falha: Linha recebida: %s\n", line);
				free(line);
			}
			close(fd_gpt);
		}
		printf("\n");

		// Teste 2: Arquivo com uma linha sem '\n'
		printf("Teste 2: Arquivo com uma linha sem '\\n'\n");
		fd_gpt = open("text_files/one_line_no_nl.txt", O_RDONLY);
		if (fd_gpt == -1) {
			perror("Erro ao abrir one_line_no_nl.txt");
		} else {
			while ((line = get_next_line(fd_gpt)) != NULL) {
				printf("Linha: %s", line);
				free(line);
			}
			close(fd_gpt);
		}
		printf("\n");

		// Teste 3: Arquivo com múltiplas linhas terminadas em '\n'
		printf("Teste 3: Arquivo com múltiplas linhas terminadas em '\\n'\n");
		fd_gpt = open("text_files/multiple_nl.txt", O_RDONLY);
		if (fd_gpt == -1) {
			perror("Erro ao abrir multiple_nl.txt");
		} else {
			while ((line = get_next_line(fd_gpt)) != NULL) {
				printf("Linha: %s", line);
				free(line);
			}
			close(fd_gpt);
		}
		printf("\n");

		// Teste 4: Arquivo gigante (linha muito longa)
		printf("Teste 4: Arquivo com linha gigante\n");
		fd_gpt = open("text_files/giant_line.txt", O_RDONLY);
		if (fd_gpt == -1) {
			perror("Erro ao abrir giant_line.txt");
		} else {
			while ((line = get_next_line(fd_gpt)) != NULL) {
				printf("Linha recebida (parcial): %.50s...\n", line);
				free(line);
			}
			close(fd_gpt);
		}
		printf("\n");

		// Teste 5: Descritor inválido
		printf("Teste 5: Descritor inválido\n");
		line = get_next_line(-1);
		if (line == NULL) {
			printf("Linha correta: (NULL)\n");
		} else {
			printf("Falha: Linha recebida: %s\n", line);
			free(line);
		}
		printf("\n");
	}

	// teste do gpt 2
	if (0) // Altere para 'if (0)' para desativar este teste
	{
		int fd1, fd2;
		char *line;

		// Abrir o primeiro arquivo
		fd1 = open("text_files/read_error.txt", O_RDONLY);
		if (fd1 == -1) {
			perror("Erro ao abrir read_error.txt");
			return 1;
		}

		// Abrir o segundo arquivo
		fd2 = open("text_files/lines_around_10.txt", O_RDONLY);
		if (fd2 == -1) {
			perror("Erro ao abrir lines_around_10.txt");
			close(fd1);
			return 1;
		}

		// Ler do fd1
		line = get_next_line(fd1);
		printf("fd1: %s", line);
		free(line);

		// Ler do fd2
		line = get_next_line(fd2);
		printf("fd2: %s", line);
		free(line);

		// Ler do fd1 novamente
		line = get_next_line(fd1);
		printf("fd1: %s", line);
		free(line);

		// Simular um erro de leitura no fd1
		// Fechando o fd1 para simular um erro de leitura
		close(fd1);

		// Tentar ler do fd1, o que deve resultar em erro
		line = get_next_line(fd1);
		if (line == NULL) {
			printf("fd1: Erro de leitura ocorreu (como esperado)\n");
		} else {
			printf("fd1: Leitura inesperada: %s", line);
			free(line);
		}

		// Continuar lendo do fd2
		line = get_next_line(fd2);
		printf("fd2: %s", line);
		free(line);

		// Reabrir fd1
		fd1 = open("text_files/read_error.txt", O_RDONLY);
		if (fd1 == -1) {
			perror("Erro ao reabrir read_error.txt");
			close(fd2);
			return 1;
		}

		// Ler do fd1 após reabrir
		line = get_next_line(fd1);
		printf("fd1: %s", line);
		free(line);

		// Ler do fd2 novamente
		line = get_next_line(fd2);
		printf("fd2: %s", line);
		free(line);

		// Fechar arquivos
		close(fd1);
		close(fd2);
	}

	printf("\n\n--- Encerrando ---\n\n");
	return (0);
}
