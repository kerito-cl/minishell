/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:25:19 by mquero            #+#    #+#             */
/*   Updated: 2025/01/25 16:12:01 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char quote_value(char c)
{
    char    quote;

    if (c == '\'')
        quote = '\'';
    else if (c == '\"')
        quote = '\"';
    else
        quote = '\0';
    return (quote);
}

void increase_counter(int *counter, char *s, int *i, char *quote)
{
    if (s[*i] == '\0')
        *counter+=1;
    while (s[*i])
    {
        if (s[*i] == *quote)
        {
            *counter+=1;
            *i+=1;
            break;
        }
        else if (*quote == '\0' && s[*i]  == ' ')
        {
            *counter+=1;
            *i+=1;
            break;
        }
        *i+=1;
        if (s[*i] == '\0')
            *counter+=1;
    }
}

int count_str(char *s)
{
    int i;
    int counter;
    char    quote;

    i = 0;
    counter = 0;
    while(s[i])
    {
        quote = quote_value(s[i]);
        i++;
        increase_counter(&counter, s, &i, &quote);
    }
    return (counter);
}

char **create_cmd(char *s)
{
    char **cmd; 
    int counter;
    int i;
    int j;
    int k;
    int y;
    char    quote;
    
    printf(" BUFFER ----> %s\n", s);
    y = 0;
    i = 0;
    j = 0;
    counter = count_str(s);
    cmd = (char **)malloc(sizeof(char *) * (counter + 2));
    if (!cmd)
        exit(1);
    cmd[counter] = NULL;
    while (s[i])
    {
        if (s[i] == ' ')
            i++;
        quote = quote_value(s[i]);
        i++;
        k = i;
        if (s[i] == '\0')
        {
            cmd[j] = ft_strndup(s + k, i - k);
            j++;
        }
        while (s[i])
        {
            if (s[i] == '$' && quote != 0)
            {
                y = 1;
                k--;
            }
            if (s[i] == quote)
            {
                cmd[j] = ft_strndup(s + k, i - k + y);
                j++;
                i++;
                break;
            }
            else if (quote == '\0' && s[i]  == ' ')
            {
                cmd[j] = ft_strndup(s + k - 1, i - k + 1);
                j++;
                i++;
                break;
            }
            i++;
            if (s[i] == '\0')
            {
                cmd[j] = ft_strndup(s + k - 1, i - k + 1);
                j++;
            }
        }
    }
    i = 0;
    while (cmd[i] != NULL)
    {
        printf("%s\n", cmd[i]);
        i++;
    }
   return (cmd);
}