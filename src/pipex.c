/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:53:44 by sfarren           #+#    #+#             */
/*   Updated: 2024/12/28 19:06:20 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid[2];
	int		file[2];

	if (argc != 5)
	{
		ft_printf("Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
		return (1);
	}
	create_pipe(pipefd);
	open_files(argv, file);
	ft_printf("file[0]: %d\n", file[0]);
	ft_printf("file[1]: %d\n", file[1]);
	pid[0] = fork();
	ft_printf("PID-1: %d\n", pid[0]);
	if (pid[0] == -1)
	{
		ft_printf("Fork failed.\n");
		exit(EXIT_FAILURE);
	}
	if (pid[0] == 0)
	{
		if (dup2(file[0], STDIN_FILENO) == -1)
		{
			perror("dup2 input file failed");
			exit(EXIT_FAILURE);
		}
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe write end failed");
			exit(EXIT_FAILURE);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		close(file[0]);
		execute_command(argv[2], envp);
		ft_printf("Child 1 exiting.\n");
		exit(EXIT_SUCCESS);
	}
	pid[1] = fork();
	if (pid[1] == -1)
	{
		ft_printf("Fork failed.\n");
		exit(EXIT_FAILURE);
	}
	if (pid[1] == 0)
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 pipe read end failed");
			exit(EXIT_FAILURE);
		}
		if (dup2(file[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 output file failed");
			exit(EXIT_FAILURE);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		close(file[1]);
		execute_command(argv[3], envp);
		exit(EXIT_SUCCESS);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	ft_printf("Parent exiting.\n");
	return (0);
}
