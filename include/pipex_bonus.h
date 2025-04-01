/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:42:03 by sfarren           #+#    #+#             */
/*   Updated: 2025/04/01 18:34:52 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	handle_pipes(int argc, char **argv, char **envp);
void	close_all_pipes(int **pipes, int num_pipes);
void	command_not_found(char **cmd);
void 	exe_command(char *cmd, char **envp, int input_fd, int output_fd)
