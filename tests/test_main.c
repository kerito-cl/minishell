#include "minishell.h" 
volatile int	g_status = 0;

void test_env(char **envp);

int main(int argc, char **argv, char **envp) {
	if (argc != 1 || **argv == '\0' || !envp) {
		return 1;
	}

	test_env(envp);

	return 0;
}
