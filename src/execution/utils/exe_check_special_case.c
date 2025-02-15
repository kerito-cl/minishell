/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_check_special_case.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 06:09:43 by ipersids          #+#    #+#             */
/*   Updated: 2025/02/15 14:09:02 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static char	*exchange_exit_code(const char *src, char *dst, int exit_code);
static char	*create_new_arg(const char *src, char *dst, char *n, int capacity);
static int	check_realloc_case(char *dst, int *capacity, int len, int code_len);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Checks for special cases `$?` in the execution of commands.
 * 
 * This function iterates through the command arguments and replaces
 * occurrences of `$?` with the exit code of the last executed command.
 * 
 * @param args The arguments passed to the command.
 * @param ms The current state of the minishell.
 * @return int Returns 1 if a special case is detected, 0 otherwise.
 */
int	exe_check_special_case(char **args, t_mshell *ms)
{
	char	*tmp;
	int		i;

	if (!args || !args[0])
		return (0);
	i = 0;
	tmp = NULL;
	while (args[i] != NULL)
	{
		if (ft_strnstr(args[i], EXIT_CODE_CASE, ft_strlen(args[i])))
		{
			tmp = exchange_exit_code(args[i], tmp, ms->exit_code);
			if (!tmp)
			{
				perror("minishell: exchange_exit_code: malloc");
				return (errno);
			}
			free(args[i]);
			args[i] = tmp;
		}
		i++;
	}
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Replaces occurrences of `$?` with the exit code in the source string.
 * 
 * @param src The source string.
 * @param dst The destination string.
 * @param exit_code The exit code to replace `$?`.
 * @return char* The new string with `$?` replaced by the exit code.
 */
static char	*exchange_exit_code(const char *src, char *dst, int exit_code)
{
	char	*code;
	size_t	capacity;

	code = ft_itoa(exit_code % 256);
	if (!code)
		return (NULL);
	capacity = ft_strlen(src) + ft_strlen(code) + ADD_CAPACITY;
	dst = malloc(capacity * sizeof(char));
	if (!dst)
	{
		free(code);
		return (NULL);
	}
	dst = create_new_arg(src, dst, code, capacity);
	free(code);
	return (dst);
}

/**
 * @brief Creates a new argument string with `$?` replaced by the exit code.
 * 
 * @param src The source string.
 * @param dst The destination string.
 * @param code The exit code as a string.
 * @param capacity The capacity of the destination string buffer.
 * @return char* The new argument string.
 */
static char	*create_new_arg(const char *src, char *dst, char *n, int capacity)
{
	size_t	code_len;
	size_t	len;

	len = 0;
	code_len = ft_strlen(n);
	while (*src != '\0')
	{
		if (check_realloc_case(dst, &capacity, len, code_len) != 0)
			return (NULL);
		if (*src == '$' && *(src + 1) == '?')
		{
			ft_memcpy(dst + len, n, code_len);
			src += 2;
			len += code_len;
			continue ;
		}
		dst[len++] = *src;
		src++;
	}
	dst[len] = '\0';
	return (dst);
}

/**
 * @brief Checks if reallocation is needed for the destination string buffer.
 * 
 * @param dst The destination string buffer.
 * @param capacity The current capacity of the destination string buffer.
 * @param len The current length of the destination string.
 * @param code_len The length of the exit code string.
 * @return int Returns EXIT_SUCCESS if reallocation is not needed or successful,
 *             otherwise returns EXIT_FAILURE.
 */
static int	check_realloc_case(char *dst, int *capacity, int len, int code_len)
{
	char	*tmp;

	tmp = NULL;
	if (len + code_len < *capacity)
		return (EXIT_SUCCESS);
	tmp = ft_realloc(dst, *capacity, len + code_len + ADD_CAPACITY);
	if (!tmp)
	{
		free(dst);
		return (EXIT_FAILURE);
	}
	*capacity = *capacity + len + code_len + ADD_CAPACITY;
	dst = tmp;
	return (EXIT_SUCCESS);
}
