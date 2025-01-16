/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:32:01 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/15 20:47:22 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_file(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: %s\n",
			file, strerror(errno));
		if (flags == O_RDONLY)
		{
			fd = open("/dev/null", O_RDONLY);
			if (fd == -1)
			{
				ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: %s\n",
					"/dev/null", strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
		else
			exit(EXIT_FAILURE);
	}
	return (fd);
}
