/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:32:01 by sfarren           #+#    #+#             */
/*   Updated: 2024/12/28 18:47:44 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	open_files(char **argv, int *fd)
{
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	fd[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[1] == -1)
	{
		perror("error opening output file");
		close(fd[0]);
		exit(EXIT_FAILURE);
	}
}

int	open_file(char *file, int flags)
{
	int	fd;

	fd = open(file, flags);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
