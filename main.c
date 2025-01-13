#include <stdio.h>
#include "minishell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

int g_signal = 0;

int main(int argc, char const **argv, char **envp)
{
    t_in in;

    (void )argc;
    if (argv)
        
    //init SIGNAL
    while (true)
    {
        in.input = readline("minishell>");
        // if g_signal == 1;
           // continue
        in.cmds = ft_split(in.input, ' ');
        if (*in.input) {
            add_history(in.input);
        }
        
        //create_builting;
        // parse function ;

        
        // childr(&t_sdfg)
        // childr(&t_sdfg)

        in.path = find_path(in.cmds[0], envp, 0);

	    execve(in.path, in.cmds , envp);
        free(in.input);
        
    }
    rl_clear_history();
    return 0;
}
