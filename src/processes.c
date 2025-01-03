/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:27:27 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/02 12:52:38 by sfarren          ###   ########.fr       */
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
		ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: %s\n", argv[2], strerror(errno));
		exit(127);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipefd[0]);
		exit(WEXITSTATUS(status));
	}
}

void	second_child_handler(int *pipefd, char **argv, char **envp)
{
	int		fd;
	pid_t	pid;
	int		status;

	// ft_printf("cmd_status: %d\n", cmd_status);
	// if (cmd_status != 0)
	// {
	// 	close(pipefd[0]);
	// 	ft_printf_fd(STDERR_FILENO, "pipex: %s: open: No such file or directory\n", argv[4]);
	// 	return;
	// }

	pid = fork_child();
	if (pid == 0)
	{
		dup2_wrapper(pipefd[0], STDIN_FILENO);
		fd = open_file(argv[4], O_CREAT | O_WRONLY | O_TRUNC);
		if (fd == -1)
			exit(EXIT_FAILURE);
		dup2_wrapper(fd, STDOUT_FILENO);
		close_fds(pipefd, 2);
		close(fd);
		execute_command(argv[3], envp);
		ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: %s\n", argv[3], strerror(errno));
		exit(127);
	}
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipefd[1]);
		exit(WEXITSTATUS(status));
	}
}

void	main_cleanup(int *pipefd, int fd)
{
	close(pipefd[0]);
	close(fd);
	waitpid(-1, NULL, 0);
}
