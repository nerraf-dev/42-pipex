/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:09 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/02 12:35:18 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_command(char *cmd, char **envp)
{
	char	**argv;
	char	*line;
	int		pipefd[2];
	pid_t	pid;
	int		status;
	int		exit_status;

	create_pipe(pipefd);
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
		line = get_next_line(pipefd[0]);
		while (line != NULL)
		{
			if (strstr(line, "not found") != NULL)
			{
				ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: %s", cmd, line);
			}
			else
			{
				ft_printf_fd(STDERR_FILENO, "%s", line);
			}
			free(line);
			line = get_next_line(pipefd[0]);
		}
		close(pipefd[0]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status == 127)
			{
				ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: command not found\n", cmd);
				exit(127);
			}
			else
				exit(exit_status);
		}
	}
	free(argv);
	exit(EXIT_FAILURE);
}

