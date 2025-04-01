/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:12:21 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/01 14:49:32 by sfarren          ###   ########.fr       */
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
	// int		pipefd[2];
	// pid_t	pid[2];
	// int		status[2];

	if (argc < 5)
		arg_error();
	else
	{
		ft_printf("Multiple pipes needed\n");
		// count number of pipes needed, argc - 4
		// create pipes
		handle_pipes(argc, argv, envp);

	}
	return (0);
}
