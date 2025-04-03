/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:47:52 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/03 14:55:51 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/pipex_bonus.h"

// static void	pipe_error(char *msg, int **pipes)
// {
// 	int	i;

// 	i = 0;
// 	perror(msg);
// 	while (i < 2)
// 	{
// 		free(pipes[i]);
// 		close(pipes[i][0]);
// 		close(pipes[i][1]);
// 		i++;
// 	}
// 	free(pipes);
// 	exit(EXIT_FAILURE);
// }

void	create_pipes(int ***pipes, int num_pipes)
{
	int	i;

	*pipes = malloc(num_pipes * sizeof(int *));
	if (!*pipes)
		exit_error("malloc", "Error allocating memory for pipes");
	i = 0;
	while (i < num_pipes)
	{
		(*pipes)[i] = malloc(2 * sizeof(int));
		if (!(*pipes)[i] || pipe((*pipes)[i]) == -1)
		{
			perror("pipe error");
			while (--i >= 0)
			{
				free((*pipes)[i]);
				close((*pipes)[i][0]);
				close((*pipes)[i][1]);
			}
			free(*pipes);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

