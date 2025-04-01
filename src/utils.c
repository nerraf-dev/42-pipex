/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:10:02 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/06 19:40:39 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief Wrapper function for dup2 system call with error handling.
 *
 * This function attempts to duplicate the file descriptor oldfd to newfd
 * using the dup2 system call. If the call fails, it prints an error message
 * and exits the program with a failure status.
 *
 * @param source_fd The file descriptor to be duplicated.
 * @param target_fd The file descriptor to be replaced.
 */
void	dup2_wrapper(int source_fd, int target_fd)
{
	if (dup2(source_fd, target_fd) == -1)
	{
		if (errno == EBADF)
			perror("Error: Invalid file descriptor");
		else if (errno == EBUSY)
			perror("Error: File descriptor is already in use");
		else if (errno == EINTR)
			perror("Error: Interrupted system call");
		else if (errno == EINVAL)
			perror("Error: Invalid argument");
		else if (errno == EMFILE)
			perror("Error: Process has too many file descriptors open");
		else
			perror("dup2 error");
		exit(EXIT_FAILURE);
	}
}

pid_t	fork_child(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		if (errno == EAGAIN)
			perror("Error: Resource temporarily unavailable");
		else if (errno == ENOMEM)
			perror("Error: Out of memory");
		else if (errno == ENOSYS)
			perror("Error: Function not supported/implemented");
		else
			perror("Fork error");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	exit_error(char *fn, char *msg)
{
	ft_printf_fd(2, "pipex: line 1: %s: %s\n", fn, msg);
	exit(EXIT_FAILURE);
}
