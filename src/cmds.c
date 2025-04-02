/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:09 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/02 12:26:40 by sfarren          ###   ########.fr       */
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
	{
		ft_printf_fd(2, "pipex: No such file or directory: %s\n", cmd[0]);
		// if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
		// 	ft_printf_fd(2, "pipex: %s: No such file or directory\n", cmd[0]);
		// else
		// 	ft_printf_fd(2, "pipex: %s: Command not found\n", cmd[0]);
	}
	else
		ft_printf_fd(2, "pipex: Command not found\n");
	free_command(cmd);
	exit(127);
}

static void	handle_execve_error(char *cmd, char *path, char **cmd_args)
{
	if (errno == ENOENT)
		ft_printf_fd(2, "pipex: %s: No such file or directory!\n", cmd);
	else if (errno == EACCES)
		ft_printf_fd(2, "pipex: %s: Permission denied\n", cmd);
	else
		perror("pipex");
	free(path);
	free_command(cmd_args);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES)
		exit(126);
	else
		exit(1);
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
		handle_execve_error(cmd[0], path, cmd);
	free(path);
	free_command(cmd);
}
