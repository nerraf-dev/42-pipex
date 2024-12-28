/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:53:44 by sfarren           #+#    #+#             */
/*   Updated: 2024/12/28 17:38:01 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
// #include <stdio.h>
// #include <fcntl.h>

int	main(int argc, char **argv)
{
	int		i;
	int		pipefd[2];
	pid_t	pid[2];

	if (argc != 5)
	{
		ft_printf("Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
		return (1);
	}
	create_pipe(pipefd);
	// Check argv[1] and [4] are files
	// pipefd[0] = open(argv[1], O_RDONLY);
	// if (pipefd[0] == -1)
	// {
	// 	perror("open");
	// 	exit(EXIT_FAILURE);
	// }
	// // O_CREAT - create if does not exists | O_WRONLY - open the file for writing | O_TRUNC - zero the file, 0644 - permissions
	// pipefd[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// if (pipefd[1] == -1)
	// {
	// 	perror("open");
	// 	exit(EXIT_FAILURE);
	// }
	open_files(argv, pipefd);
	ft_printf("pipefd 1: %d\n", pipefd[0]);
	ft_printf("pipefd 2: %d\n", pipefd[1]);

	// Check argv[2] and [3] are commands

	ft_printf("Number of arguments: %d\n", argc);
	ft_printf("Arguments provided:\n");
	i = 1;
	while (i < argc)
	{
		ft_printf("argv[%d]: %s\n", i, argv[i]);
		i++;
	}
	pid[0] = fork();
	ft_printf("PID-1: %d\n", pid[0]);
	if (pid[0] == -1)
	{
		ft_printf("Fork failed.\n");
		exit(EXIT_FAILURE);
	}
	else if (pid[0] == 0)
	{
		ft_printf("Do something in child 1\n");
		ft_printf("Child 1 exiting.\n");
		exit(EXIT_SUCCESS);
	}
	// else
	// {
	// 	// ft_printf("Child is PID %d\n", (intmax_t) pid);
	// 	ft_printf("Parent exiting.\n");
	// 	exit(EXIT_SUCCESS);
	// }
	pid[1] = fork();
	ft_printf("PID-2: %d\n", pid[1]);
	if (pid[1] == -1)
	{
		ft_printf("Fork failed.\n");
		exit(EXIT_FAILURE);
	}
	else if (pid[1] == 0)
	{
		ft_printf("Do something in child 2\n");
		ft_printf("Child 2 exiting.\n");
		exit(EXIT_SUCCESS);
	}

	// Parent process
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	ft_printf("Parent exiting.\n");

	return (0);
}
