/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipersids <ipersids@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:52:30 by ipersids          #+#    #+#             */
/*   Updated: 2025/01/24 23:51:51 by ipersids         ###   ########.fr       */
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

static void	test_echo(char *str);
static void test_export(const char *command, t_env *env);
static void test_unset(const char *command, t_env *env);

void test_builtin(t_env *env) {
	
	printf("\n\n%s-------------- TEST ECHO --------------%s\n\n", PURPLE, DEFAULT);
	
	test_echo("just a string without options '-n'");
	test_echo("-n just a string with only on option '-n'");
	test_echo("-n -n -n just a string with a few '-n'");
	test_echo("-n -n -n-n just a string with a few '-n' and some wrong options");
	test_echo("- -n -n-n just a string with a wrong option at the start");
	test_echo("just a string with a back slash things \\avvv \\n\'");
	test_echo("");

	printf("\n\n%s--------------- TEST ENV --------------%s\n\n", PURPLE, DEFAULT);

	char *env_args[] = {
		"env",
		NULL
	};
	builtin_env(&(env_args[1]), env);

	printf("\n%sTest error message:%s\n", RED, DEFAULT);
	char *env_args2[] = { "env", "-p", NULL };
	builtin_env(&(env_args2[1]), env);

	printf("\n\n%s-------------- TEST EXPORT ------------%s\n\n", PURPLE, DEFAULT);

	test_export("export TEST TEST1= TEST2=test", env);
	test_export("export TEST=test1 TEST2=", env);
	test_export("export 1TEST TEST2=test2", env);
	test_export("export _TEST=_test test=small_test", env);
	test_export("export TEST6", env);
	test_export("export", env);

	printf("\n\n%s-------------- TEST UNSET -------------%s\n\n", PURPLE, DEFAULT);

	test_unset("unset TEST TEST1= TEST2=test", env);
	test_unset("unset TEST=test1 TEST2=", env);
	test_unset("unset 1TEST TEST2=test2", env);
	test_unset("unset _TEST test", env);
	test_unset("unset TEST6", env);

	printf("\n\n%s-------------- TEST PWD --------------%s\n\n", PURPLE, DEFAULT);

	char *pwd_str = NULL;
	pwd_str = "hello";
	builtin_pwd(NULL);
	builtin_pwd(&pwd_str);

	printf("\n\n%s-------------- TEST EXIT --------------%s\n\n", PURPLE, DEFAULT);

	t_mshell ms;

	ms.env.envp = env->envp;
	ms.env.len = env->len;
	ms.env.capacity = env->capacity;
	ms.exit_code = 0;

	char *exit_args[] = {"ghk", "123", "-125", "214f", NULL};
	// builtin_exit(&(exit_args[1]), &ms);	// output $? = 123 + 'exit' message
	// builtin_exit(NULL, &ms);				// output $? = 0 + 'exit' message
	// builtin_exit(&(exit_args[2]), &ms);	// output $? = 125 + 'exit' message
	// builtin_exit(&(exit_args[3]), &ms);	// output $? = 255 + 'exit' message + error message
	builtin_exit(exit_args, &ms); 		// error message (doesn't exit)

	printf("\n\n%s--------------- TEST CD ---------------%s\n\n", PURPLE, DEFAULT);

	char *path_cd[] = {"/home/ipersids/Documents", NULL, "Documents", NULL};

	printf("\nGo to %s:\n", *path_cd);
	printf("Before:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));
	builtin_cd(path_cd, env);
	printf("After:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));

	printf("\nGo HOME: %s\n", env_find_value("HOME", env));
	printf("Before:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));
	builtin_cd(NULL, env);
	printf("After:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));

	printf("\nGo to %s:\n", path_cd[2]);
	printf("Before:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));
	builtin_cd(&(path_cd[2]), env);
	printf("After:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));

	printf("\nUnset OLDRWD\n");
	env_remove("OLDPWD", env);
	printf("Before:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));
	builtin_cd(NULL, env);
	printf("After:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));

	printf("\nUnset PWD\n");
	env_remove("PWD", env);
	printf("Before:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));
	builtin_cd(NULL, env);
	printf("After:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));

	printf("\nUnset HOME\n");
	env_remove("HOME", env);
	printf("Before:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));
	builtin_cd(NULL, env);
	printf("After:\nOLDPWD = %s,\nPWD = %s\n", env_find_value("OLDPWD", env), env_find_value("PWD", env));
}



static void test_unset(const char *command, t_env *env) {
	char **arr = NULL;
	size_t i = 0;

	printf("%s\nTesting command:%s %s\n", GREEN, DEFAULT, command);
	arr = ft_split(command, ' ');
	if (!arr)
	{
		perror(strerror(errno));
		return ;
	}

	printf("\nBEFORE:\n");
	for (int j = 1; arr[j] != NULL; j++) {
		printf("Checking if variable '%s' exists in environment: ", arr[j]);
		if (env_find_variable(arr[j], env, &i))
			printf("%sYes%s\n", GREEN, DEFAULT);
		else
			printf("%sNo%s\n", RED, DEFAULT);
	}
	printf(">>>\n");
	builtin_unset(arr, env);
	printf("\nAFTER:\n");
	for (int j = 1; arr[j] != NULL; j++) {
		printf("Checking if variable '%s' exists in environment: ", arr[j]);
		if (env_find_variable(arr[j], env, &i))
			printf("%sYes%s\n", GREEN, DEFAULT);
		else
			printf("%sNo%s\n", RED, DEFAULT);
	}
	
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

static void test_export(const char *command, t_env *env) {
	char **arr = NULL;
	size_t i = 0;

	printf("%s\nTesting command:%s %s\n", GREEN, DEFAULT, command);
	arr = ft_split(command, ' ');
	if (!arr)
	{
		perror(strerror(errno));
		return ;
	}
	builtin_export(&arr[1], env);
	for (int j = 1; arr[j] != NULL; j++) {
		printf("\nChecking if variable '%s' exists in environment: ", arr[j]);
		if (env_find_variable(arr[j], env, &i))
			printf("%sYes%s\nResult: %s\n", GREEN, DEFAULT, env->envp[i]);
		else
			printf("%sNo%s\n", RED, DEFAULT);
	}
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

static void	test_echo(char *str) {
	char **arr = NULL;

	printf("%sTest string:%s %s\n", GREEN, DEFAULT, str);
	arr = ft_split(str, ' ');
	if (!arr)
	{
		perror(strerror(errno));
		return ;
	}
	printf("%sstart >>>%s\n", RED, DEFAULT);
	builtin_echo(arr);
	printf("%s<<< end%s\n\n",  RED, DEFAULT);
	int i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}
