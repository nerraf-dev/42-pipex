/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:09 by sfarren           #+#    #+#             */
/*   Updated: 2024/12/30 15:31:22 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_command(char *cmd, char **envp)
{
	char	**argv;
	char	buffer[256];
	ssize_t	bytes_read;
	int		pipefd[2];
	pid_t	pid;
	int		status;
	int		exit_status;
	int		len;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	argv = (char **)malloc(sizeof(char *) * 4);
	if (!argv)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	argv[0] = "/bin/sh";
	argv[1] = "-c";
	argv[2] = cmd;
	argv[3] = NULL;
	pid = fork_child();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDERR_FILENO);
		close(pipefd[1]);
		execve("/bin/sh", argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[1]);
		bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			len = ft_strlen(buffer);
			if (ft_strnstr(buffer, "not found", len) != NULL)
				ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: command not found\n", cmd);
			else
				ft_printf_fd(STDERR_FILENO, "%s", buffer);
		}
		close(pipefd[0]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status == 127)
			{
				exit(127);
			}
			else
			{
				exit(exit_status);
			}
		}
	}
	free(argv);
	exit(EXIT_FAILURE);
}

// void	execute_command(char *cmd, char **envp)
// {
// 	char	**argv;

// 	argv = (char **)malloc(sizeof(char *) * 4);
// 	if (!argv)
// 	{
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	argv[0] = "/bin/sh";
// 	argv[1] = "-c";
// 	argv[2] = cmd;
// 	argv[3] = NULL;
// 	// // Check command exists:
// 	// if (access(cmd, F_OK) == -1)
// 	// {
// 	// 	ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: %s\n", cmd, strerror(errno));
// 	// 	free(argv);
// 	// 	exit(0);
// 	// }
// 	execve("/bin/sh", argv, envp);
// 	ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: %s\n", cmd, strerror(errno));
// 	free(argv);
// 	exit(0);
// }
