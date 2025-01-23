/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_split_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:04:57 by mquero            #+#    #+#             */
/*   Updated: 2025/01/23 17:28:56 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	count_words(const char *s);
static char	*extract_word(const char *s, int *index);
static int	calculate_word_length(const char *s, int *index, int *in_quotes);

/* --------------------------- Public Functions ---------------------------- */

char	**exe_split_command(char *input)
{
	int		word_count;
	char	**arr;
	int		i;
	int		index;

	word_count = count_words(input);
	arr = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	index = 0;
	while (i < word_count)
	{
		arr[i] = extract_word(input, &index);
		if (!arr[i])
		{
			free_2d_array(arr, i);
			return (NULL);
		}
		i++;
	}
	arr[word_count] = NULL;
	return (arr);
}

/* ------------------- Private Function Implementation --------------------- */

static int	calculate_word_length(const char *s, int *index, int *in_quotes)
{
	int	len;

	len = 0;
	while (s[*index] && ((*in_quotes && s[*index] != '\'') || (!(*in_quotes)
				&& s[*index] != ' ')))
	{
		(*index)++;
		len++;
	}
	return (len);
}

static char	*extract_word(const char *s, int *index)
{
	int		start;
	int		len;
	int		in_quotes;
	char	*word;

	len = 0;
	in_quotes = 0;
	while (s[*index] == ' ')
		(*index)++;
	start = *index;
	if (s[*index] == '\'')
	{
		in_quotes = 1;
		(*index)++;
		start++;
	}
	len = calculate_word_length(s, index, &in_quotes);
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + start, len + 1);
	word[len] = '\0';
	if (in_quotes && s[*index] == '\'')
		(*index)++;
	return (word);
}

static int	count_words(const char *s)
{
	int	count;
	int	in_quotes;

	count = 0;
	in_quotes = 0;
	while (*s)
	{
		if (*s == '\'')
			in_quotes = !in_quotes;
		else if (!in_quotes && (*s != ' ' && (*(s + 1) == ' ' \
				|| *(s + 1) == '\0')))
			count++;
		else if (in_quotes && *(s + 1) == '\'' && (*(s + 2) == ' ' \
				|| *(s + 2) == '\0'))
			count++;
		s++;
	}
	return (count);
}
