/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:53:14 by mquero            #+#    #+#             */
/*   Updated: 2025/02/13 01:00:25 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = 0;

// minishell> cat <<EOF1 | grep hello | cat << EOF2 > out.txt | ls
// AST before:
// ---------
// Type: 22, Value: 
//   Type: 22, Value: 
//     Type: 22, Value: 
//       Type: 24, Value: EOF1 (left)
//         Type: 28, Value: cat (right)
//       Type: 24, Value: EOF2 (right)
//         Type: 22, Value: 
//           Type: 22, Value: 
//             Type: 25, Value: out.txt (right)
//               Type: 28, Value: cat (right)
//   Type: 28, Value: ls (right)

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
		printf("AST before:\n---------\n");
        print_ast(ms.root, 0, "ms.root");
		printf("AST after:\n---------\n");
		print_ast(ms.root, 0, "ms.root");
		//exe_ast_tree(ms.root, &ms);
		// printf("exit code: %d\n", ms.exit_code);
		add_history(ms.input);
		free(ms.input);
		free_ast(ms.root); /** @bug set ms.root to NULL in free_ast to avoid segfault in ./minishell <cntr+D> case */
	}
	// write(1, "Good luck!\n", 11);
	exit_destroy_minishell(&ms);
	return (0);
}
