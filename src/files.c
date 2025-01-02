/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:32:01 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/02 13:05:48 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_files(char **argv, int *fd)
{
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
	{
		ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: %s\n", argv[1], strerror(errno));
		fd[0] = open("/dev/null", O_RDONLY); // Open /dev/null if input file is missing
	}
	fd[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: %s\n", argv[4], strerror(errno));
		close(fd[0]);
		exit(EXIT_FAILURE);
	}
}

int	open_file(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: %s\n", file, strerror(errno));
		if (flags == O_RDONLY)
			fd = open("/dev/null", O_RDONLY); // Open /dev/null if input file is missing
		else
			exit(EXIT_FAILURE);
	}
	return (fd);
}
