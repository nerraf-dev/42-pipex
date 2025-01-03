/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 13:45:41 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/03 13:04:01 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

pid_t	fork_child(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error();
	return (pid);
}

	// {
	// 	perror("Fork");
	// 	exit(EXIT_FAILURE);
	// }
