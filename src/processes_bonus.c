/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:27:27 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/03 14:57:20 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/pipex_bonus.h"


void	fork_children(int **pipes, int num_cmds, char **argv, char **envp)
{
	int	i;
	int	pid;
	int	fd_in;
	int	fd_out;

	i = 0;
	while (i < num_cmds)
	{
		pid = fork_child();
		if (pid == 0)
		{
			if (i == 0)
			{
				fd_in = open_file(argv[1], O_RDONLY);
				dup2_wrapper(fd_in, STDIN_FILENO);
				dup2_wrapper(pipes[i][1], STDOUT_FILENO);
				close(fd_in);
			}
			else if (i == num_cmds - 1)
			{
				fd_out = open_file(argv[num_cmds + 2], O_CREAT | O_WRONLY | O_TRUNC);
				dup2_wrapper(pipes[i - 1][0], STDIN_FILENO);
				dup2_wrapper(fd_out, STDOUT_FILENO);
				close(fd_out);
			}
			else
			{
				dup2_wrapper(pipes[i - 1][0], STDIN_FILENO);
				dup2_wrapper(pipes[i][1], STDOUT_FILENO);
			}
			close_all_pipes(pipes, num_cmds);
			execute_command(argv[i + 2], envp);
			exit(EXIT_FAILURE);
		}
		else if (pid < 0)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
