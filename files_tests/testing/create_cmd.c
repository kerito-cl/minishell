/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:25:19 by mquero            #+#    #+#             */
/*   Updated: 2025/01/24 13:49:41 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int count_str(char *s)
{
    int i;
    int counter;
    char    quote;

    i = 0;
    counter = 0;
    while(s[i])
    {
        if (s[i] == '\'')
            quote = '\'';
        else if (s[i] == '\"')
            quote = '\"';
        else
            quote = '\0';
        i++;
        while (s[i])
        {
            if (s[i] == quote)
            {
                counter++;
                break;
            }
            else if (quote == '\0' && s[i]  == ' ')
            {
                counter++;
                break;
            }
            i++;
            if (s[i] == '\0' && counter == 0)
                counter++;
        }
    }
    printf("%d\n", counter);
    return 0;
}

char **create_cmd(char *s)
{
   char **cmd; 
    int counter;

    counter = count_str(s);

   cmd = (char **)malloc(sizeof(char *) * 100);

   return cmd;
}