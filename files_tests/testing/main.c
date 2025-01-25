/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:53:14 by mquero            #+#    #+#             */
/*   Updated: 2025/01/25 13:03:44 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

void print_values(char *values) 
{
    if (values)
        printf("%s", values);
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
int main(int argc, char const **argv)
{
    char *input;
    t_ast *root;
    rl_hook_func_t sig;
    (void )argc;
    if (argv)
        
    rl_catch_signals = 0;
    signal(SIGINT, continue_signal);
    signal(SIGQUIT, slash_signal);
    rl_event_hook = hook_signal;
    while (true)
    {
        input = readline("minishell>");
        if (input == NULL)
            exit(1);
        root = parse_input(input);
        //print_ast(root, 0);
        free_ast(root);

        //add_history(in.input);
        //create_builting;
        // parse function ;

        // childr(&t_sdfg)
        // childr(&t_sdfg)
        /*if (in.cmds[0] != NULL )
        {
            in.path = find_path(in.cmds[0], envp, 0);
	        execve(in.path, in.cmds , envp);
        }*/
        
    }
    rl_clear_history();
    return 0;
}
