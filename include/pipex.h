/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:00:48 by sfarren           #+#    #+#             */
/*   Updated: 2024/12/28 17:41:11 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// # include <stddef.h>
// # include <stdlib.h>
// # include <unistd.h>
# include "../lib/include/libft.h"
# include <stdio.h>
# include <fcntl.h>

// pipe.c
int		create_pipe(int *pipefd);

// cmds.c
void	execute_command(char *cmd, char **envp);

// files.c
void	open_files(char **argv, int *fd);

#endif
