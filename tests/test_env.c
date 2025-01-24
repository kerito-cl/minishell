/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 22:46:10 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 23:51:43 by ipersids         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef COLORS
# define COLORS
# 	define RED "\033[0;31m"
# 	define GREEN "\033[0;32m"
# 	define PURPLE "\033[0;35m"
# 	define DEFAULT "\033[0m"
#endif

void test_env(char **envp) {
	t_env env;

	if (init_environment(envp, &env) != 0)
	{
		printf("init_environment(envp, &env) fails\n");
		exit(EXIT_FAILURE);
	}

	printf("\n\033[0;32mEnvironment was successfully initialized:\033[0m");
	printf("\n\t- len = %u,\n\t- capacity = %u.\n\n", env.len, env.capacity);

	printf("\n\n%s------------- PRINT ALL VARIABLES -------------%s\n\n", PURPLE, DEFAULT);
	for (unsigned int i = 0; i < env.len; i++) {
		printf("%s\n", env.envp[i]);
	}
	printf("\n\n%s----------------- END OF PRINT ----------------%s\n\n", PURPLE, DEFAULT);

	printf("\n\n%s---------------- FIND VARIABLE ----------------%s\n\n", PURPLE, DEFAULT);

	printf("\n%sTry to find variable%s \"USER=\": \n", PURPLE, DEFAULT);
	size_t j = 0;
	if (env_find_variable("USER=", &env, &j) != NULL)
		printf("%sFOUND!%s -> '%s', index = %zu\n", GREEN, DEFAULT, env.envp[j], j);
	else
		printf("%sHmm, something wrong!%s index = %zu\n", RED, DEFAULT, j);
	
	printf("\n%sTry to find variable%s \"PATH\": \n", PURPLE, DEFAULT);
	j = 0;
	if (env_find_variable("PATH", &env, &j) != NULL)
		printf("%sFOUND!%s -> '%s', index = %zu\n", GREEN, DEFAULT, env.envp[j], j);
	else
		printf("%sHmm, something wrong!%s index = %zu\n", RED, DEFAULT, j);

	printf("\n%sTry to find variable%s \"PATH5\" (not exist): \n", PURPLE, DEFAULT);
	j = 0;
	if (env_find_variable("PATH5", &env, &j) != NULL)
		printf("%sFOUND!%s -> '%s', index = %zu\n", GREEN, DEFAULT, env.envp[j], j);
	else
		printf("NOT HERE! I expected it! index = %zu (%s)\n", j, env.envp[j]);
	
	printf("\n\n%s----------------- ADD VARIABLE ----------------%s\n\n", PURPLE, DEFAULT);

	printf("%sTry to add existing variable%s \"USER=aaaaaa\"\n", PURPLE, DEFAULT);
	printf("exit_code %d\n", env_add("USER=aaaaaa", &env));
	printf("\n%sTry to find variable%s \"USER=\": \n", PURPLE, DEFAULT);
	j = 0;
	if (env_find_variable("USER=", &env, &j) != NULL)
		printf("%sFOUND!%s -> '%s', index = %zu\n", GREEN, DEFAULT, env.envp[j], j);
	else
		printf("%sHmm, something wrong!%s index = %zu\n", RED, DEFAULT, j);
	
	printf("%sTry to add new variable%s \"TEST=test\"\n", PURPLE, DEFAULT);
	printf("exit_code %d\n", env_add("TEST=test", &env));

	printf("\n%sTry to find variable%s \"TEST=test\": \n", PURPLE, DEFAULT);
	j = 0;
	if (env_find_variable("TEST=test", &env, &j) != NULL)
		printf("%sFOUND!%s -> '%s', index = %zu\n", GREEN, DEFAULT, env.envp[j], j);
	else
		printf("%sHmm, something wrong!%s index = %zu\n", RED, DEFAULT, j);
	
	printf("\n%sEnvironment:%s len = %u, capacity = %u\n", PURPLE, DEFAULT, env.len, env.capacity);

	printf("\n\n%s-------------- REMOVE VARIABLE ---------------%s\n\n", PURPLE, DEFAULT);
	j = 0;
	printf("\n%sTry remove existing variable%s \"USER\"\n", PURPLE, DEFAULT);
	if (env_remove("USER=", &env) == 0 && env_find_variable("USER=", &env, &j) == NULL)
		printf("Item removed! len = %u\n", env.len);
	else
		printf("Hmm, something wrong! len = %u\n", env.len);
	
	printf("\n%sTry remove not existing variable%s \"USER\"\n", PURPLE, DEFAULT);
	unsigned int tmp_len = env.len;
	if (env_remove("USER=", &env) == 0 && env_find_variable("USER=", &env, &j) == NULL && tmp_len == env.len)
		printf("Expected result! len = %u\n", env.len);
	else
		printf("Hmm, something wrong! len = %u\n", env.len);

	printf("\n\n%s------------ RETURN VARIABLE VALUE ------------%s\n\n", PURPLE, DEFAULT);

	j = 0;
	printf("HOME:\n");
	printf("Line found: %s\n", env_find_variable("HOME", &env, &j));
	printf("Returned value of HOME: %s\n", env_find_value("HOME", &env));
	printf("Returned value of $HOME: %s\n", env_find_value("$HOME", &env));

	j = 0;
	printf("\nTEST6 (do not exist):\n");
	printf("Line found: %s\n", env_find_variable("TEST6", &env, &j));
	printf("Returned value of TEST6: %s\n", env_find_value("TEST6", &env));
	printf("Returned value of $TEST6: %s\n", env_find_value("$TEST6", &env));

	printf("\n\n%s------------ FREEING ENVIRONMENT --------------%s\n\n", PURPLE, DEFAULT);
	printf("\nFREEING!\n");
	free_environment(&env);
	printf("%sEnvironment:%s len = %u, capacity = %u\n", PURPLE, DEFAULT, env.len, env.capacity);
}
