/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:37:01 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/07 14:22:03 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/**
 * @brief Retrieves the system PATH variable from the environment variables.
 *
 * This function searches through the provided environment variables (envp) to
 * find the PATH variable. If the PATH variable is not found, it uses a default
 * path. The function then splits the PATH variable into an array of strings,
 * each representing a directory in the PATH.
 *
 * @param envp The environment variables array.
 * @return A NULL-terminated array of strings, each representing a directory in
 * the PATH.
 */
static char	**get_paths(char **envp)
{
	char	*def_path;
	char	*path_var;
	int		i;

	def_path = "/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/sbin";
	if (!envp || !envp[0])
		return (ft_split(def_path, ':'));
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	if (!envp[i])
		return (ft_split(def_path, ':'));
	path_var = envp[i] + 5;
	return (ft_split(path_var, ':'));
	// else
	// 	envp[i] += 5;
	// return (ft_split(envp[i], ':'));
}

/**
 * @brief Finds the full path of a command by searching through an array of
 * directory paths.
 *
 * This function iterates through the provided array of directory paths,
 * appending the command name to each directory path and checking if the
 * resulting full path exists. If a valid path is found, it is returned. If no
 * valid path is found, the function returns NULL.
 *
 * @param paths An array of directory paths to search through.
 * @param cmd The command name to find the full path for.
 * @return A string containing the full path of the command if found, or NULL
 * if not found.
 */
static char	*find_cmd_path(char **paths, char *cmd)
{
	char	*dir_path;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		dir_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(dir_path, cmd);
		free(dir_path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Frees a null-terminated array of strings.
 *
 * This function iterates through each string in the provided array,
 * frees each string, and then frees the array itself.
 *
 * @param paths A null-terminated array of strings to be freed.
 */
static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/**
 * get_path - Retrieves the full path of a given command.
 * @cmd: The command to find the path for.
 * @envp: The environment variables array.
 *
 * This function searches for the given command in the directories
 * specified by the PATH environment variable. If the command is found,
 * it returns the full path to the command. If the command or environment
 * variables are NULL, or if the command cannot be found, it returns NULL.
 *
 * Return: The full path to the command, or NULL if not found.
 */
char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;

	if (!cmd)
		return (NULL);
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	path = find_cmd_path(paths, cmd);
	free_paths(paths);
	return (path);
}
