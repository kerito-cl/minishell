#include <stdio.h>
#include "minishell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char const **argv, char **envp)
{
    t_in in;
    rl_hook_func_t sig;
    (void )argc;
    if (argv)
        
    rl_catch_signals = 0;
    signal(SIGINT, continue_signal);
    signal(SIGQUIT, slash_signal);
    rl_event_hook = hook_signal;
    while (true)
    {
        in.input = readline("minishell>");
        if (in.input == NULL)
            exit(1);

        in.cmds = ft_split(in.input, ' ');
        //add_history(in.input);
        //create_builting;
        // parse function ;

        
        // childr(&t_sdfg)
        // childr(&t_sdfg)
        if (in.cmds[0] != NULL )
        {
            in.path = find_path(in.cmds[0], envp, 0);
	        execve(in.path, in.cmds , envp);
        }
        free(in.input);
        
    }
    rl_clear_history();
    return 0;
}
