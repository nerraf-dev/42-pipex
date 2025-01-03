/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:00:48 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/02 12:52:44 by sfarren          ###   ########.fr       */
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
int		create_pipe(int *pipefd);

// cmds.c
void	execute_command(char *cmd, char **envp);

// files.c
void	open_files(char **argv, int *fd);
int		open_file(char *file, int flags);

// processes.c
void	first_child_handler(int *pipefd, int fd, char **argv, char **envp);
void	second_child_handler(int *pipefd, char **argv, char **envp);
void	main_cleanup(int *pipefd, int fd);

// utils.c
pid_t	fork_child(void);
void	dup2_wrapper(int oldfd, int newfd);
void	close_fds(int *fds, int count);

#endif
