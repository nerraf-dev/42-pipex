/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:26:09 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/01 19:50:14 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/pipex_bonus.h"

// void	exe_command(char *cmd, char **envp, int input_fd, int output_fd)
// {
// 	dup2_wrapper(input_fd, STDIN_FILENO);
// 	dup2_wrapper(output_fd, STDOUT_FILENO);
// 	close(input_fd);
// 	close(output_fd);
// 	execve(get_command_path(cmd), ft_split(cmd, ' '), envp);
// 	perror("execve");
// 	exit(EXIT_FAILURE);
// }
