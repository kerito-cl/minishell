/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:10:10 by mquero            #+#    #+#             */
/*   Updated: 2025/01/28 18:40:51 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void    dollar_to_value(char *s1, char *var)

char    *handle_dollar_sign(char *input, char **envp)
{
    t_env   envir;
    t_elem   elem;
    char    *var;
    char    *temp;

    envir.envp = envp;
    elem.i = 0;
    elem.len = ft_strlen(input);
    elem.new_len = ft_strlen(input);
    var = ft_calloc(sizeof(char) , (elem.len + 1));
    temp = NULL;
    while (*input)
    {
        while (*input != '$' &&  *input)
        {
            var[elem.i] = *input;
            elem.i++;
            input++;
        }
        if (*input == '$' && *input + 1 == '\0')
        {
            printf("DASADSASD\n");
            var[elem.i] = *input;
            elem.i++;
        }
        else if (*input == '$' && *input + 1 != '\0')
        {
            temp = env_find_value_v2(input, &envir);
            if (temp != NULL)
            {
                elem.new_len = elem.len + ft_strlen(temp);
                var = ft_realloc(var, elem.len, elem.new_len);
                elem.len = elem.new_len;
                while (*temp)
                {
                    var[elem.i] = *temp;
                    elem.i++;
                    temp++;
                }
            }
            while (*input != '\0' && !ft_strchr(" \"'<>|", *input))
                input++;
        }
        else if (*input != '\0')
            input++;
        printf("%s\n", var);
    }
    return (var);
}