/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:00:48 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/08 14:05:41 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// # include <stddef.h>
// # include <stdlib.h>
// # include <unistd.h>
# include "../lib/include/libft.h"
# include "../lib/include/get_next_line.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

// pipe.c
void	create_pipe(int *pipefd);
void	close_pipe(int *pipefd);

// cmds.c
void	execute_command(char *cmd, char **envp);

// files.c
// void	open_files(char **argv, int *fd);
int		open_file(char *file, int flags);

// paths.c
char	*get_path(char *cmd, char **envp);

// processes.c
void	child_handler(int pipe_write, char **argv, char **envp);
void	parent_handler(int pipe_read, char **argv, char **envp);
void	main_cleanup(int *pipefd, int fd);

// utils.c
pid_t	fork_child(void);
void	dup2_wrapper(int source_fd, int target_fd);
void	exit_error(char *fn, char *msg);

// split.c
char	**split_command(char *str);

#endif
