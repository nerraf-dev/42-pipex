/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:12:21 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/03 14:55:41 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/pipex_bonus.h"

static void	arg_error(int argc)
{
	if (argc < 5)
	{
		ft_printf_fd(2, "Error: Bad arguments\n");
		ft_printf_fd(2, "Usage: %s file1 cmd1 cmd2 file2\n", "pipex");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		**pipes;	// Array of pipes, each pipe is an int[2]
	int		fd[2];		// File descriptors for input and output
	int		i;
	int		num_pipes;
	int		num_cmds;

	// Check if the number of arguments is valid
	arg_error(argc);
	num_cmds = argc - 3;	// Number of commands to execute
	num_pipes = argc - 4;	// Number of pipes needed

	// Allocate memory for an array of int[2] for the pipes
	// Create the pipes:
	create_pipes(&pipes, num_pipes);
	//	allocate the memory to pipes[i]
	// 	create the pipe with create_pipe(int *pipefd)
	// Allocate memory for an array for PIDs
	// Create fork processes:
	// 	fork the process
	//  connect the pipes
	// Ensure redirection
	//  execute the command
	//  close the pipes
	//  wait for the processes to finish
	fork_children(pipes, num_cmds, argv, envp);
	// Close all pipes
	close_all_pipes(pipes, num_pipes);
	// Free allocated memory
	i = 0;
	while (i < num_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	// Wait for all child processes to finish
	wait_for_children(num_cmds);
	// Close file descriptors
	close(fd[0]);
	close(fd[1]);
	// Return the exit status of the last command
	if (WIFEXITED(fd[1]))
		return (WEXITSTATUS(fd[1]));
	else if (WIFSIGNALED(fd[1]))
	{
		ft_printf("Child %d was terminated by signal %d\n", i, WTERMSIG(fd[1]));
		return (WTERMSIG(fd[1]));
	}
	else
	{
		ft_printf("Child %d exited with status %d\n", i, WEXITSTATUS(fd[1]));
		return (WEXITSTATUS(fd[1]));
	}
	return (0);
}
