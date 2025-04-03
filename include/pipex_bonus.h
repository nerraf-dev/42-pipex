/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:42:03 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/03 14:55:30 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	handle_pipes(int argc, char **argv, char **envp);
void	close_all_pipes(int **pipes, int num_pipes);
void	command_not_found(char **cmd);
void	create_pipes(int ***pipes, int num_pipes);
void	fork_children(int **pipes, int num_cmds, char **argv, char **envp);
void	wait_for_children(int num_children);
// void	exe_command(char *cmd, char **envp, int input_fd, int output_fd);
