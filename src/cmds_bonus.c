/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:09 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/01 14:59:54 by sfarren          ###   ########.fr       */
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

void	execute_command(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = split_command(argv);
	if (!cmd || !cmd[0])
		command_not_found(cmd);
	path = get_path(cmd[0], envp);
	if (!path)
		command_not_found(cmd);
	if (execve(path, cmd, envp) == -1)
	{
		perror("execve");
		free(path);
		free_command(cmd);
		exit(126);
	}
	free(path);
	free_command(cmd);
}
