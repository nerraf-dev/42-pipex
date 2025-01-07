/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:27:27 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/07 12:14:16 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_handler(int pipe_write, char **argv, char **envp)
{
	int		file_in;

	file_in = open_file(argv[1], O_RDONLY);
	dup2_wrapper(file_in, STDIN_FILENO);
	dup2_wrapper(pipe_write, STDOUT_FILENO);
	close(file_in);
	close(pipe_write);
	execute_command(argv[2], envp);
}

void	parent_handler(int pipe_read, char **argv, char **envp)
{
	int		file_out;

	file_out = open_file(argv[4], O_CREAT | O_WRONLY | O_TRUNC);
	dup2_wrapper(pipe_read, STDIN_FILENO);
	dup2_wrapper(file_out, STDOUT_FILENO);
	close(pipe_read);
	close(file_out);
	execute_command(argv[3], envp);
}

void	main_cleanup(int *pipefd, int fd)
{
	close(pipefd[0]);
	close(fd);
	waitpid(-1, NULL, 0);
}
