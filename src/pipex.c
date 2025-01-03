/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:53:44 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/02 16:27:11 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	int		fd;
	int		status;


	if (argc == 5)
	{
		

	}
	else
	{
		ft_printf("Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
	}
	create_pipe(pipefd);
	fd = open_file(argv[1], O_RDONLY);
	first_child_handler(pipefd, fd, argv, envp);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		close(fd);
		return (WEXITSTATUS(status));
	}
	second_child_handler(pipefd, argv, envp);
	main_cleanup(pipefd, fd);
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
