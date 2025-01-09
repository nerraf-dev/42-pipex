/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:32:01 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/08 20:22:24 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	open_file(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n",
			file, strerror(errno));
		if (flags == O_RDONLY)
		{
			fd = open("/dev/null", O_RDONLY);
			ft_printf("NO input: NULL fd: %d\n", fd);
			if (fd == -1)
			{
				ft_printf_fd(STDERR_FILENO, "pipex: %s: %s\n",
					"/dev/null", strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
		else
			exit(EXIT_FAILURE);
	}
	return (fd);
}
