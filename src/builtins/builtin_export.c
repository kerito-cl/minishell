/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:34:58 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/18 14:57:53 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	is_variable_name_valid(const char *var);
static int	print_sorted_export(char **var_arr, unsigned int len);
static void	bubble_sort(char **arr, unsigned int size);

/* --------------------------- Public Functions ---------------------------- */

/**
 * @brief Executes the export command.
 * 
 * This function mimics the behavior of the export command. It adds or updates
 * environment variables. If no arguments are provided, it prints 
 * the environment variables in a sorted order.
 * 
 * @param args Array of arguments passed to the export command.
 * @param env Pointer to the environment struct containing an array of strings.
 * @return int Returns 0 on success, or an error code if an invalid variable 
 * 			   name is provided.
 */
int	builtin_export(char **args, t_env *env)
{
	size_t	i;
	int		exit_code;

	if (!args || args[0] == NULL)
		return (print_sorted_export(env->envp, env->len));
	i = 0;
	exit_code = 0;
	while (args[i] != NULL)
	{
		if (!is_variable_name_valid(args[i]))
		{
			printf("minishell: export: '%s': isn't a valid identifier\n", \
					args[i]);
			exit_code = ERROR_BUILTIN_EXPORT_INV_VAR;
		}
		else
		{
			env_add(args[i], env);
			exit_code = 0;
		}
		i++;
	}
	return (exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

/**
 * @brief Checks if the given variable name is valid.
 * 
 * Allowed characters: letters (`a-z`, `A-Z`), digits (`0-9`) 
 * and underscore (`_`). Variable names cannot start with a digit or be empty.
 * 
 * @param var The variable name to check.
 * @return int Returns 1 if the variable name is valid, 0 otherwise.
 */
static int	is_variable_name_valid(const char *var)
{
	size_t	i;

	if (!var || ft_isdigit(var[0]) || var[0] == '\0')
		return (0);
	i = 0;
	while (var[i] != '\0' && var[i] != '=')
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Prints the environment variables in a sorted order.
 * 
 * This function prints the environment variables in a sorted order 
 * and in a specific format: `declare -x TEST="2"` or `declare -x TEST1`.
 * 
 * @param var_arr Array of environment variables.
 * @param len Length of the environment variable array.
 * @return int Returns 0 on success.
 */
static int	print_sorted_export(char **var_arr, unsigned int len)
{
	char	**tmp;
	char	*ch;
	size_t	i;

	tmp = (char **) malloc(len * sizeof(char *));
	if (!tmp)
		return (ERROR_MALLOC_FAILS);
	ft_memcpy(tmp, var_arr, len * sizeof(char *));
	bubble_sort(tmp, len);
	i = 0;
	while (i < len)
	{
		ch = ft_strchr(tmp[i], '=');
		if (!ch)
			printf("declare -x %s\n", tmp[i++]);
		else
		{
			*ch = '\0';
			printf("declare -x %s=\"%s\"\n", tmp[i++], ch + 1);
		}
	}
	free(tmp);
	return (0);
}

/**
 * @brief Sorts an array of strings using bubble sort.
 * 
 * @param arr Array of strings to sort.
 * @param size Size of the array.
 */
static void	bubble_sort(char **arr, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	char			*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				tmp = arr[j];
				arr[j] = arr[i];
				arr[i] = tmp;
			}
			j++;
		}
		i++;
	}
}
