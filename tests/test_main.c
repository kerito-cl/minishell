#include "minishell.h" 
volatile sig_atomic_t	g_status = 0;

void test_env(char **envp);
void test_builtin(t_env *env);
void test_pipex_exernal_cmd(char *cmd1, char *cmd2, t_mshell *ms);

void print_values(char *values) 
{
    if (values) {
            printf("%s", values);
    }
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

int main(int argc, char **argv, char **envp) {
	if (argc != 1 || !argv || !envp)
	{
		ft_putstr_fd("Usage: ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}


	// // test 1
	// test_env(envp);

	// // test 3
	// t_env env;
	// env_init(envp, &env);
	// test_builtin(&env);
	// if (env.envp != NULL)
	// 	env_free(&env);

	// test 4
	t_mshell ms;
	env_init(envp, &ms.env);
	ms.exit_code = -255;
	ms.interactive_mode = isatty(STDIN_FILENO);
	// test_pipex_exernal_cmd("pwd", "cat src/main.c", &ms);

	t_ast *root = parse_input("cd ../ hd");
	print_ast(root, 0);

	exe_ast_tree(root, &ms);

	free_ast(root);
	env_free(&ms.env);
	
	return 0;
}
