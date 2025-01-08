/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_printf_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:37:03 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/08 14:42:13 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "../include/pipex.h"

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("Failed to create temporary file");
		exit(EXIT_FAILURE);
	}
}

void	test_ft_printf_fd(void)
{
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;

	fd = open_file("temp_test_file.txt");
	ft_printf_fd(fd, "Error: %s\n", "Test error message");
	lseek(fd, 0, SEEK_SET);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read == -1)
	{
		perror("Failed to read from temporary file");
		close(fd);
		return ;
	}
	buffer[bytes_read] = '\0';
	if (strcmp(buffer, "Error: Test error message\n") == 0)
		printf("Test passed: Error message written correctly\n");
	else
		printf("Test failed: Unexpected output: %s\n", buffer);
	close(fd);
	remove("temp_test_file.txt");
}

int	main(void)
{
	test_ft_printf_fd();
	return (0);
}
