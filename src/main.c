/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:53:14 by mquero            #+#    #+#             */
/*   Updated: 2025/02/14 15:53:10 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

/* --------------------- Private function prototypes ----------------------- */

static void	run_shell(t_mshell *ms, int *fake_code);

/* --------------------------- Public Functions ---------------------------- */
void print_values(char **values, char *type) 
{
    if (values) {
        for (int i = 0; values[i] != NULL; i++) {
            printf("%s (%s)", values[i], type);
            if (values[i + 1] != NULL) {
                printf(", "); // Separate multiple values with a comma
            }
        }
    }
	else
		printf("(%s)", type);
}

void print_ast(t_ast *node, int depth, char *type)
{
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("Type: %d, Value: ", node->type);
    print_values(node->value, type);
    printf("\n");
    if (node->left || node->right) {
        print_ast(node->left, depth + 1, "left");
        print_ast(node->right, depth + 1, "right");
    }
}
int	main(int argc, char **argv, char **envp)
{
	t_mshell			ms;
	int					fake_code;

	if (argc != 1 || !argv || !envp)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}
	init_minishell_struct(&ms, envp);
	sig_interceptor(SIG_INTERACTIVE_MODE);
	run_shell(&ms, &fake_code);
	exit_destroy_minishell(&ms);
	return (0);
}

/* ------------------- Private Function Implementation --------------------- */

static void	run_shell(t_mshell *ms, int *fake_code)
{
	while (1)
	{
		*fake_code = -1;
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
		ms->root = parse_input(ms->input, ms->env.envp, fake_code);
		//print_ast(ms->root, 0, "root");
		if (!ms->root && *fake_code != 0)
			ms->exit_code = ERROR_SYNTAX_HEREDOC;
		if (ms->root && exe_heredoc_preprocessor(ms->root, ms) == 0)
			exe_ast_tree(ms->root, ms);
		add_history(ms->input);
		free(ms->input);
		free_ast(ms->root);
	}
}
