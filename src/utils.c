/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 14:10:02 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/02 22:55:30 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path(char *cmd, char **envp)
{
	char	*path;
	char	**paths;
	char	*dir_path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		dir_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(dir_path, cmd);
		free(dir_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;qsort
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void	dup2_wrapper(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
}

void	close_fds(int *fds, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(fds[i]);
		i++;
	}
}

pid_t	fork_child(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
