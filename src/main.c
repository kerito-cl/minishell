/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:53:14 by mquero            #+#    #+#             */
/*   Updated: 2025/02/14 14:35:59 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

/* --------------------- Private function prototypes ----------------------- */

static void	run_shell(t_mshell *ms);

/* --------------------------- Public Functions ---------------------------- */

int	main(int argc, char **argv, char **envp)
{
	t_mshell			ms;

	if (argc != 1 || !argv || !envp)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}
	init_minishell_struct(&ms, envp);
	sig_interceptor(SIG_INTERACTIVE_MODE);
	run_shell(&ms);
	exit_destroy_minishell(&ms);
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

static void	run_shell(t_mshell *ms)
{
	while (1)
	{
		ms->root = NULL;
		ms->input = readline("\033[0;35mminishell*w* \033[0m");
		sig_to_exit_code(ms);
		if (ms->input == NULL)
		{
			ms->exit_code = 0;
			break ;
		}
		if (ms->input[0] == '\0')
		{
			free(ms->input);
			continue ;
		}
		ms->root = parse_input(ms->input, ms->env.envp);
		if (!ms->root)
			ms->exit_code = ERROR_SYNTAX_HEREDOC;
		if (ms->root && exe_heredoc_preprocessor(ms->root, ms) == 0)
			exe_ast_tree(ms->root, ms);
		add_history(ms->input);
		free(ms->input);
		free_ast(ms->root);
	}
}
