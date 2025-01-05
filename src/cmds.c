/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:09 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/03 21:24:59 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*get_path(char *cmd, char **envp)
{
	char	*path;
	char	**paths;
	char	*dir_path;
	int		i;
	char	*default_path = "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin";

	if (!cmd)
		return (NULL);
	if (!envp || !envp[0])
		envp = (char *[]){default_path, NULL};
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		envp = (char *[]){default_path, NULL};
	else
		envp[i] += 5;
	paths = ft_split(envp[i], ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		dir_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(dir_path, cmd);
		free(dir_path);
		if (access(path, F_OK) == 0)
		{
			i = -1;
			while (paths[++i])
				free(paths[i]);
			free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

void	execute_command(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	cmd = split_command(argv);
	if (!cmd || !cmd[0])
	{
		ft_printf_fd(2, "pipex: command not found\n");
		exit(EXIT_FAILURE);
	}
	path = get_path(cmd[0], envp);
	if (!path)
	{
		ft_printf_fd(2, "pipex: %s: command not found\n", cmd[0]);
		i = 0;
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror("execve");
		free(path);
		i = 0;
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
		exit(EXIT_FAILURE);
	}
	free(path);
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

// void	execute_command(char *argv, char **envp)
// {
// 	char	**cmd;
// 	int		i;
// 	char	*path;

// 	i = -1;
// 	cmd = split_command(argv);
// 	if (!cmd || !cmd[0])
// 	{
// 		ft_printf_fd(2, "pipex: command not found\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	path = get_path(cmd[0], envp);
// 	if (!path)
// 	{
// 		while (cmd[++i])
// 			free(cmd[i]);
// 		free(cmd);
// 		ft_printf_fd(2, "pipex: %s: command not found\n", cmd[0]);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (execve(path, cmd, envp) == -1)
// 	{
// 		perror("execve");
// 		free(path);
// 		i = -1;
// 		while (cmd[++i])
// 			free(cmd[i]);
// 		free(cmd);
// 		exit(EXIT_FAILURE);
// 	}
// 	free(path);
// 	i = -1;
// 	while (cmd[++i])
// 		free(cmd[i]);
// 	free(cmd);
// }

