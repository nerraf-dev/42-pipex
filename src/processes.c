/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:27:27 by sfarren           #+#    #+#             */
/*   Updated: 2024/12/29 15:10:28 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_child_handler(int *pipefd, int fd, char **argv, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork_child();
	if (pid == 0)
	{
		dup2_wrapper(fd, STDIN_FILENO);
		dup2_wrapper(pipefd[1], STDOUT_FILENO);
		close_fds(pipefd, 2);
		close(fd);
		execute_command(argv[2], envp);
		perror("execute_command");
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
	{
		close(pipefd[0]);
		close(fd);
		exit(EXIT_FAILURE);
	}
}

void	second_child_handler(int *pipefd, char **argv, char **envp)
{
	int		fd;
	pid_t	pid;

	pid = fork_child();
	if (pid == 0)
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 pipe read end");
			exit(EXIT_FAILURE);
		}
		fd = open_file(argv[4], O_CREAT | O_WRONLY | O_TRUNC);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 output file");
			exit(EXIT_FAILURE);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		close(fd);
		execute_command(argv[3], envp);
		perror("execute_command");
		exit(EXIT_FAILURE);
	}
}

void	main_cleanup(int *pipefd, int fd)
{
	close(pipefd[0]);
	close(fd);
	waitpid(-1, NULL, 0);
}
