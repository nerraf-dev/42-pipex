/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:27:27 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/06 20:04:15 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	child_handler(int *pipefd, char **argv, char **envp)
{
	int		file_in;

	file_in = open_file(argv[1], O_RDONLY);
	dup2_wrapper(file_in, STDIN_FILENO);
	dup2_wrapper(pipefd[1], STDOUT_FILENO);
	close(file_in);
	close_pipe(pipefd);
	execute_command(argv[2], envp);
}

void	parent_handler(int *pipefd, char **argv, char **envp)
{
	int		file_out;

	file_out = open_file(argv[4], O_CREAT | O_WRONLY | O_TRUNC);
	dup2_wrapper(pipefd[0], STDIN_FILENO);
	dup2_wrapper(file_out, STDOUT_FILENO);
	close_pipe(pipefd);
	close(file_out);
	execute_command(argv[3], envp);
}

void	main_cleanup(int *pipefd, int fd)
{
	close(pipefd[0]);
	close(fd);
	waitpid(-1, NULL, 0);
}
