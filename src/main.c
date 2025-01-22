/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:53:14 by mquero            #+#    #+#             */
/*   Updated: 2025/01/22 13:58:00 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_status = 0;

void print_values(char *values) 
{
    if (values) {
            printf("%s", values);
    }
}

void print_ast(t_ast *node, int depth)
{
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("Type: %d, Value: ", node->type);
    print_values(node->value);
    printf("\n");
    if (node->left || node->right) {
        print_ast(node->left, depth + 1);
        print_ast(node->right, depth + 1);
    }
}
int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	char				*line;
	t_env				env;
    t_ast *root;

	if (argc != 1 || !argv || !envp)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}
	env_init(envp, &env);
	sig_sigaction_init(&sa, sig_handler_main);
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			break ;
        root = parse_input(line);
        print_ast(root, 0);
		add_history(line);
		free(line);
	}
	rl_clear_history();
	free(line);
	env_free(&env);
	write(1, "Good luck!\n", 11);
	return (0);
}
