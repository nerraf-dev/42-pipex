/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:09 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/01 18:36:33 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	free_command(char **cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	command_not_found(char **cmd)
{
	if (cmd && cmd[0])
		ft_printf_fd(2, "pipex: line 1: %s: command not found\n", cmd[0]);
	else
		ft_printf_fd(2, "pipex: command not found\n");
	free_command(cmd);
	exit(127);
}

void exe_command(char *cmd, char **envp, int input_fd, int output_fd)
{
	dup2_wrapper(input_fd, STDIN_FILENO);
	dup2_wrapper(output_fd, STDOUT_FILENO);
	close(input_fd);
	close(output_fd);
	execve(get_command_path(cmd), ft_split(cmd, ' '), envp);
	perror("execve");
	exit(EXIT_FAILURE);
}
