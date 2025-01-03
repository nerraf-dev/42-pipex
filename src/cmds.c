/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:09 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/03 13:19:45 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_command(char *argv, char **envp)
{
	char	**cmd;
	int		i;
	char	*path;

	i = -1;
	// split the cmd from any arguments
	cmd = ft_split(argv, ' ');
	// find the path of the command
	path = get_path(cmd[0], envp);
	// if the path is not found
	if (!path)
	{
		// free the cmd
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	// execute the command
	if (execve(path, cmd, envp) == -1)
		error();
}

