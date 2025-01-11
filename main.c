#include <stdio.h>
#include "minishell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char const **argv, char **envp)
{
    char *input;
    char *path;
    char  **input_split;

    (void )argc;
    if (argv)
        
    while (true)
    {
        input = readline("minishell>");
        input_split = ft_split(input, ' ');

        if (*input) {
            add_history(input);
        }
        path = find_path(input_split[0], envp, 0);
	    execve(path, input_split, envp);
        free(input);
    }
    return 0;
}
