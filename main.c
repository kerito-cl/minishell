#include <stdio.h>
#include "minishell.h"
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

int g_signal = 0;

void exit_signal(int signal)
{
    g_signal = signal;
    g_signal = 3;
}

void continue_signal(int signal)
{
    //printf("SIGNAL IS %d\n", signal);
    g_signal = signal;
            //write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();

}

int main(int argc, char const **argv, char **envp)
{
    t_in in;

    (void )argc;
    if (argv)
        
    //signal(EOF, exit_signal);
    signal(SIGINT, continue_signal);
    while (true)
    {
        in.input = readline("minishell>");
        if (g_signal == SIGINT)
        {
            continue;
        }
        if (in.input == NULL)
        {
            write(1, "\n", 1);
            exit(1);
        }
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
