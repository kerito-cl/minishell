/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:34:58 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/30 07:16:21 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* --------------------- Private function prototypes ----------------------- */

static int	print_sorted_export(char **var_arr, unsigned int len);
static void	bubble_sort(char **arr, unsigned int size);
static int	export_error_check(char *arg, int i, int *is_ignored);

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
	int		is_ignored;

	if (!args || args[0] == NULL)
	{
		exit_code = print_sorted_export(env->envp, env->len);
		if (exit_code != 0)
			perror("minishell: export");
		return (exit_code);
	}
	i = 0;
	exit_code = 0;
	while (args[i] != NULL)
	{
		is_ignored = 0;
		exit_code = export_error_check(args[i], i, &is_ignored);
		if (i == 0 && exit_code == ERROR_INVALID_OPTION)
			return (exit_code);
		if (exit_code == 0 && is_ignored == 0)
			exit_code = env_add(args[i], env);
		i++;
	}
	return (exit_code);
}

/* ------------------- Private Function Implementation --------------------- */

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
	size_t	i;
	size_t	j;

	tmp = (char **) malloc(len * sizeof(char *));
	if (!tmp)
		return (errno);
	ft_memcpy(tmp, var_arr, len * sizeof(char *));
	bubble_sort(tmp, len);
	i = -1;
	while (++i < len)
	{
		j = 0;
		if (!(tmp[i][0] == '_' && (tmp[i][1] == '\0' || tmp[i][1] == '=')))
		{
			printf("declare -x ");
			while (tmp[i][j] != '=' && tmp[i][j] != '\0')
				printf("%c", tmp[i][j++]);
			if (tmp[i][j] == '=')
				printf("=\"%s\"\n", &tmp[i][j + 1]);
			else
				printf("\n");
		}
	}
	return (free(tmp), 0);
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

static int	export_error_check(char *arg, int i, int *is_ignored)
{
	if (i == 0 && arg[0] == '-')
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': options are not supperted\nexport", STDERR_FILENO);
		ft_putstr_fd(" : usage: export [name[=value] ...]\n", STDERR_FILENO);
		return (ERROR_INVALID_OPTION);
	}
	if (!builtin_is_identifier_valid(arg))
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (ERROR_GENERIC);
	}
	if (arg[0] == '_' && (arg[1] == '\0' || arg[1] == '='))
		*is_ignored = 1;
	return (0);
}
