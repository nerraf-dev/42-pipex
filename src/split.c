/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfarren <sfarren@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 18:07:42 by sfarren           #+#    #+#             */
/*   Updated: 2025/01/03 18:11:36 by sfarren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	count_words(char *str)
{
	int		count;
	int		in_word;
	int		i;
	char	quote;

	count = 0;
	in_word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' && !in_word)
			i++;
		else if (is_quote(str[i]))
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i])
				i++;
			count++;
			in_word = 0;
		}
		else
		{
			while (str[i] && str[i] != ' ' && !is_quote(str[i]))
				i++;
			count++;
			in_word = 0;
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
	if (is_quote(**str))
	{
		quote = *(*str)++;
		while ((*str)[len] && (*str)[len] != quote)
			len++;
		word = ft_substr(*str, 0, len);
		*str += len + 1;
	}
	else
	{
		while ((*str)[len] && (*str)[len] != ' ' && !is_quote((*str)[len]))
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
