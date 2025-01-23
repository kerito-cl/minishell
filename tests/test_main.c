#include "minishell.h" 
volatile int	g_status = 0;

void test_env(char **envp);
void test_builtin(t_env *env);
void test_pipex_exernal_cmd(char *cmd1, char *cmd2, t_mshell *ms);

int main(int argc, char **argv, char **envp) {
	if (argc != 1 || !argv || !envp)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}

	t_mshell ms;

	// // test 1
	// test_env(envp);

	// // test 3
	// t_env env;
	// env_init(envp, &env);
	// test_builtin(&env);
	// if (env.envp != NULL)
	// 	env_free(&env);

	ms.env.envp = NULL;
	ms.exit_code = -255;
	ms.interactive_mode = isatty(STDIN_FILENO);
	test_pipex_exernal_cmd("ls -la", "cat", &ms);
	
	return 0;
}
