/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:12:14 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/01 18:38:18 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief Waits for all child processes to finish.
 *
 * This function loops through the number of child processes and waits for each
 * one to finish using `waitpid`. It also collects and prints the exit status
 * of each child process for debugging purposes.
 *
 * @param num_children The number of child processes to wait for.
 */
void	wait_for_children(int num_children)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_children)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			perror("waitpid");
			i++;
			continue ;
		}
		if (WIFEXITED(status))
			ft_printf("Child %d exited with status %d\n", i, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			ft_printf("Child %d was terminated by signal %d\n", i, WTERMSIG(status));
		i++;
	}
}

/**
 * @brief Closes all unused file descriptors for the current process.
 *
 * This function iterates through all the pipes and closes any file descriptors
 * that are not needed for the current command. This is essential to avoid
 * resource leaks and ensure proper behavior of the pipeline.
 *
 * @param pipes A dynamically allocated array of pipes (each pipe is an int[2]).
 * @param num_pipes The total number of pipes.
 * @param current The index of the current command in the pipeline.
 */
void	close_unused_fds(int **pipes, int num_pipes, int current)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		// Close the read end of the pipe if it's not needed
		if (i != current - 1)
			close(pipes[i][0]);

		// Close the write end of the pipe if it's not needed
		if (i != current)
			close(pipes[i][1]);
		i++;
	}
}

void	close_all_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close_pipe(pipes[i]);
		i++;
	}
}

void	handle_pipes(int argc, char **argv, char **envp)
{
	int	**pipes;
	int	i;
	int	input_fd;
	int	output_fd;

	i = 0;
	pipes = malloc((argc - 4) * sizeof(int *));
	if (!pipes)
		exit_error("malloc", "Failed to allocate memory for pipes");

	i = 0;
	while (i < argc - 4)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i])
			exit_error("malloc", "Failed to allocate memory for pipe");
		create_pipe(pipes[i]);
		i++;
	}

	i = 0;
	while (i < argc - 3) // Loop through commands
	{
		if (i == 0) // First command
			input_fd = open(argv[1], O_RDONLY);
		else
			input_fd = pipes[i - 1][0];

		if (i == argc - 4) // Last command
			output_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			output_fd = pipes[i][1];

		if (fork_child() == 0)
		{
			close_unused_fds(pipes, argc - 4, i);
			exe_command(argv[i + 2], envp, input_fd, output_fd);
		}

		close(input_fd);
		close(output_fd);
		i++;
	}
	close_all_pipes(pipes, argc - 4);
	i = 0;
	while (i < argc - 4)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	wait_for_children(argc - 3);
}
