/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:45:21 by sfarren           #+#    #+#             */
/*   Updated: 2024/11/30 21:48:47 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// for read
# include <fcntl.h>
// for mallloc and free
# include <stdlib.h>
// for read
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/**
 * @brief Reads a line from a file descriptor.
 *
 * @param fd The file descriptor to read from.
 * @return A pointer to the line read from the file descriptor,
 * or NULL if there are no more lines to read or an error occurs.
 */
char	*get_next_line(int fd);

/**
 * @brief Duplicates a string.
 *
 * @param str The string to duplicate.
 * @return A pointer to the duplicated string.
 */
char	*gnl_strdup(char *str);

/**
 * @brief Extracts a substring from a string.
 *
 * @param s The string to extract the substring from.
 * @param start The starting index of the substring.
 * @param len The length of the substring.
 * @return A pointer to the extracted substring.
 */
char	*gnl_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Calculates the length of a string.
 *
 * @param str The string to calculate the length of.
 * @return The length of the string.
 */
size_t	gnl_strlen(const char *str);

/**
 * @brief Concatenates two strings.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return A pointer to the concatenated string.
 */
char	*gnl_str_join(char const *s1, char const *s2);

/**
 * @brief Frees the memory allocated for a buffer.
 *
 * @param str The buffer to free.
 * @return A pointer to NULL.
 */
char	*gnl_free_buf(char **str);

/**
 * @brief Finds the index of the first occurrence of a
 * newline character in a string.
 *
 * @param str The string to search.
 * @return The index of the first occurrence of a
 * newline character, or -1 if not found.
 */
int		gnl_find_nl(const char *str);

#endif
