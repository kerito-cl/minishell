#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char const **argv)
{
    char *input;

    while (true)
    {
        input = readline("minishell>");

        if (*input) {
            add_history(input);
        }
        printf("You entered: %s\n", input);
        free(input);
    }
    return 0;
}
