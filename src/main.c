/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:53:14 by mquero            #+#    #+#             */
/*   Updated: 2025/02/13 20:47:45 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

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

	if (argc != 1 || !argv || !envp)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}
	init_minishell_struct(&ms, envp);
	sig_interceptor(SIG_INTERACTIVE_MODE);
	while (1)
	{
		ms.root = NULL;
		ms.input = readline("minishell> ");
		sig_to_exit_code(&ms);
		if (ms.input == NULL)
		{
			ms.exit_code = 0;
			break ;
		}
		if (ms.input[0] == '\0')
		{
			free(ms.input);
			continue;
		}
        ms.root = parse_input(ms.input, ms.env.envp); /** @bug if nothing allocated better to return NULL; case ./minishell <ENTER> (line is empty) */
		// print_ast(ms.root, 0, "ms.root");
		exe_heredoc_preprocessor(ms.root, &ms);
		exe_ast_tree(ms.root, &ms);
		add_history(ms.input);
		free(ms.input);
		free_ast(ms.root); /** @bug set ms.root to NULL in free_ast to avoid segfault in ./minishell <cntr+D> case */
	}	
	exit_destroy_minishell(&ms);
	return (0);
}

