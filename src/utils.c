/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:10:02 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/03 18:21:51 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"



void	dup2_wrapper(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	close_fds(int *fds, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(fds[i]);
		i++;
	}
}

pid_t	fork_child(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
