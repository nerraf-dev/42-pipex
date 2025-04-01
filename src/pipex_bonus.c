/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:12:21 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/01 20:46:13 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/pipex_bonus.h"

static void	arg_error(void)
{
	ft_printf_fd(2, "Error: Bad arguments\n");
	ft_printf_fd(2, "Usage: %s file1 cmd1 cmd2 file2\n", "pipex");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	int		num_cmds;
	int		**pipes;
	int		*pids;
	int		fd[2];
	int		i;
	int		j;

	if (argc < 5)
		arg_error();

	num_cmds = argc - 3;
	pipes = malloc((num_cmds - 1) * sizeof(int *));
	if (!pipes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	pids = malloc(num_cmds * sizeof(int));
	if (!pids)
	{
		perror("malloc");
		free(pipes);
		exit(EXIT_FAILURE);
	}

	ft_printf("Multiple pipes needed\n");
	ft_printf("File In: %s - File Out: %s\n", argv[1], argv[argc - 1]);
	create_pipes(pipes, num_cmds - 1);

	// Fork child processes
	i = 0;
	while (i < num_cmds)
	{
		pids[i] = fork_child();
		if (pids[i] == 0)
		{
			// Child process
			if (i == 0)
			{
				fd[0] = open_file(argv[1], O_RDONLY);
				dup2_wrapper(fd[0], STDIN_FILENO);
				dup2_wrapper(pipes[i][1], STDOUT_FILENO);
				close(fd[0]);
			}
			else if (i == num_cmds - 1)
			{
				fd[1] = open_file(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC);
				dup2_wrapper(pipes[i - 1][0], STDIN_FILENO);
			}
			else
			{
				dup2_wrapper(pipes[i - 1][0], STDIN_FILENO);
				dup2_wrapper(pipes[i][1], STDOUT_FILENO);
			}
			// Close all pipes in the child process
			j = 0;
			while (j < num_cmds - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
				j++;
			}

			// Execute the command
			execute_command(argv[i + 2], envp);
			exit(EXIT_FAILURE);
		}
		i++;
	}

	// Close all pipes in the parent process
	i = 0;
	while (i < num_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}

	// Wait for all child processes
	i = 0;
	while (i < num_cmds)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}

	// Free allocated memory
	i = 0;
	while (i < num_cmds - 1)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(pids);

	return (0);
}
