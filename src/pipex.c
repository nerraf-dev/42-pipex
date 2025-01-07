/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:53:44 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/07 14:25:34 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	arg_error(void)
{
	ft_printf_fd(2, "Error: Bad arguments\n");
	ft_printf_fd(2, "Usage: %s file1 cmd1 cmd2 file2\n", "pipex");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid[2];
	int		status[2];

	if (argc != 5)
		arg_error();
	create_pipe(pipefd);
	pid[0] = fork_child();
	if (pid[0] == 0)
	{
		close(pipefd[0]);
		child_handler(pipefd[1], argv, envp);
	}
	pid[1] = fork_child();
	if (pid[1] == 0)
	{
		close(pipefd[1]);
		parent_handler(pipefd[0], argv, envp);
	}
	close_pipe(pipefd);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	if (WIFEXITED(status[1]))
		return (WEXITSTATUS(status[1]));
	return (EXIT_FAILURE);
}
