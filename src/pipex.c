/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:53:44 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/06 20:02:54 by sfarren          ###   ########.fr       */
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
	pid_t	pid1;

	if (!envp || !envp[0])
		envp = NULL;
	if (argc == 5)
	{
		create_pipe(pipefd);
		pid1 = fork_child();
		if (pid1 == 0)
			child_handler(pipefd, argv, envp);
		waitpid(pid1, NULL, 0);
		parent_handler(pipefd, argv, envp);
	}
	else
		arg_error();
	close_pipe(pipefd);
	return (0);
}
