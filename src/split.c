/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:07:42 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/06 17:22:48 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	skip_quote(char **str, char quote)
{
	(*str)++;
	while (**str && **str != quote)
		(*str)++;
	if (**str)
		(*str)++;
}

static void	skip_word(char **str)
{
	while (**str && **str != ' ' && **str != '\'' && **str != '\"')
		(*str)++;
}

static int	count_words(char *str)
{
	int		count;
	char	quote;

	count = 0;
	while (*str)
	{
		if (*str == ' ')
			str++;
		else if (*str == '\'' || *str == '\"')
		{
			quote = *str;
			skip_quote(&str, quote);
			count++;
		}
		else
		{
			skip_word(&str);
			count++;
		}
	}
	return (count);
}

static char	*get_next_word(char **str)
{
	char	*word;
	int		len;
	char	quote;

	len = 0;
	while (**str == ' ')
		(*str)++;
	if (**str == '\'' || **str == '\"')
	{
		quote = *(*str)++;
		while ((*str)[len] && (*str)[len] != quote)
			len++;
		word = ft_substr(*str, 0, len);
		*str += len + 1;
	}
	else
	{
		while ((*str)[len] && (*str)[len] != ' ' && (*str)[len] != '\'' &&
			(*str)[len] != '\"')
			len++;
		word = ft_substr(*str, 0, len);
		*str += len;
	}
	return (word);
}

char	**split_command(char *str)
{
	char	**words;
	int		count;
	int		i;

	i = 0;
	count = count_words(str);
	words = (char **)malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	while (i < count)
	{
		words[i] = get_next_word(&str);
		i++;
	}
	words[i] = NULL;
	return (words);
}
