/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:09 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/09 14:28:18 by sfarren          ###   ########.fr       */
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

static void	command_not_found(char **cmd)
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
	int		i;

	cmd = split_command(argv);
	if (!cmd || !cmd[0])
		command_not_found(cmd);
	path = get_path(cmd[0], envp);
	if (!path)
		command_not_found(cmd);
	ft_printf("Executing: %s\n", cmd[0]);
	i = 0;
	while (cmd[i])
	{
		ft_printf("Arg %d: %s\n", i, cmd[i]);
		i++;
	}
	ft_printf("Path: %s\n", path);
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
