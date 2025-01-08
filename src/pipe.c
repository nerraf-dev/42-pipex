/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:47:52 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/08 14:01:21 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief Creates a pipe and stores the file descriptors in the provided array.
 *
 * This function creates a pipe using the pipe() system call and stores the
 * file descriptors in the array pointed to by pipefd. If the pipe creation
 * fails, an error message is printed to stderr and the program exits with
 * a failure status.
 *
 * @param pipefd An array of two integers where the file descriptors for the
 *               read and write ends of the pipe will be stored.
 * @return Returns 0 on success.
 */
void	create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe error");
		exit(EXIT_FAILURE);
	}
}

void	close_pipe(int *pipefd)
{
	int	fd1;
	int	fd2;

	fd1 = close(pipefd[0]);
	fd2 = close(pipefd[1]);
	if (fd1 == -1 || fd2 == -1)
	{
		ft_printf_fd(2, "pipex: line 1: pipe failed to close\n");
	}
}
