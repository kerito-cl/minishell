/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:10:10 by mquero            #+#    #+#             */
/*   Updated: 2025/01/27 17:42:02 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void    dollar_to_value(char *s1, char *var)

void    handle_dollar_sign(char **envp, t_token *tokens, int len)
{
    t_env   envir;
    t_elem   elem;
    //char    *var;
    char    *temp;

    envir.envp = envp;
    elem.i = 0;
    while (elem.i <= len)
    {
        elem.j = 0;
        if (tokens[elem.i].cmd)
        {
            while(tokens[elem.i].cmd[elem.j])
            {
                if (tokens[elem.i].cmd[elem.j][0] == '\"' ||
                tokens[elem.i].cmd[elem.j][0] == '$')
                {
                    temp = tokens[elem.i].cmd[elem.j];
                    //printf("%s\n", temp);
                    env_find_value_v2(temp, &envir);
                    //printf("%s\n", var);
                    //dollar_to_value(temp, var);
                }
                elem.j++;
            }
        }
        elem.i++;
    }
}