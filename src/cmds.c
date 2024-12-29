/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:09 by sfarren           #+#    #+#             */
/*   Updated: 2024/12/29 19:06:46 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


void	execute_command(char *cmd, char **envp)
{
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * 4);
	if (!argv)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	argv[0] = "/bin/sh";
	argv[1] = "-c";
	argv[2] = cmd;
	argv[3] = NULL;
	execve("/bin/sh", argv, envp);
	// ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: command not found\n", cmd);
	ft_printf_fd(STDERR_FILENO, "pipex: line 1: %s: %s\n", cmd, strerror(errno));
	// perror("execve");
	free(argv);
	exit(127);
}
