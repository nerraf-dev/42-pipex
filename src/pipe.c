/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:47:52 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/03 12:56:08 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	create_pipe(int *pipefd)
{
	if (pipe(pipefd) == -1)
		error();
	return (0);
}

	// {
	// 	perror("pipe error");
	// 	exit(EXIT_FAILURE);
	// }
