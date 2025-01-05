/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:27:27 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/03 20:50:16 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_handler(int *fd, char **argv, char **envp)
{
	int		file_in;

	file_in = open_file(argv[1], O_RDONLY);
	dup2_wrapper(file_in, STDIN_FILENO);
	dup2_wrapper(fd[1], STDOUT_FILENO);
	close(file_in);
	execute_command(argv[2], envp);
}

void	parent_handler(int *fd, char **argv, char **envp)
{
	int		file_out;

	file_out = open_file(argv[4], O_CREAT | O_WRONLY | O_TRUNC);
	dup2_wrapper(fd[0], STDIN_FILENO);
	dup2_wrapper(file_out, STDOUT_FILENO);
	close(fd[1]);
	execute_command(argv[3], envp);
}

void	main_cleanup(int *pipefd, int fd)
{
	close(pipefd[0]);
	close(fd);
	waitpid(-1, NULL, 0);
}
