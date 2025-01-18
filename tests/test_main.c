#include "minishell.h" 
volatile int	g_status = 0;

void test_env(char **envp);
void test_builtin(t_env *env);

int main(int argc, char **argv, char **envp) {
	if (argc != 1 || **argv == '\0' || !envp) {
		return 1;
	}

	// test_env(envp);
	t_env env;
	env_init(envp, &env);
	test_builtin(&env);
	
	if (env.envp != NULL)
		env_free(&env);
	return 0;
}
