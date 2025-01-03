/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:53:44 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/03 16:06:03 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc == 5)
	{
		create_pipe(fd);
		// create fork
		pid1 = fork_child();
		// if child (pid == 0)
		if (pid1 == 0)
			child_handler(fd, argv, envp);
		// wait for child to end
		waitpid(pid1, NULL, 0);
		// run parent process
		parent_handler(fd, argv, envp);
	}
	else
	{
		ft_printf_fd(2, "\033[31mError: Bad arguments\n\e[0m");
		ft_printf("Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
	}
	// close pipe
	close(fd[0]);
	close(fd[1]);
	return (0);
}
