/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:49:00 by mquero            #+#    #+#             */
/*   Updated: 2025/01/24 14:09:06 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


char  *deal_with_quotes(char *input)
{
    int i;
    int j;
    int k;
    t_flags flag;
    char *buffer;
    char  quote;

    k = 0;
    i = 0;
    j = 0;
    flag.a = false;
    flag.b = false;
    buffer = (char *)malloc(sizeof(char) * ft_strlen(input) * 2);
    if (!buffer)
        return (NULL);
    ft_bzero(buffer, sizeof(char) * ft_strlen(input) * 2);
    while (input[i])
    {
        while (input[i] == '<' || input[i] == '>' || input[i] == '|')
        {
            buffer[j] = input[i];
            j++;
            i++;
        }
        k = i;
        while (input[k])
        {
            if (input[k] == '\'')
            {
                flag.a = true;
                quote = '\'';
                break;
            }
            if (input[k] == '\"')
            {
                flag.a = true;
                quote = '\"';
                break;
            }   
            if (input[k] == ' ')
               break;
            k++;
        }
        if (flag.a)
        {
            buffer[j] = quote;
            j++;
            while (input[i])
            {
                if (input[i] != quote)
                {
                    buffer[j] = input[i];
                    j++;
                }
                else if (input[i] == quote && i != k)
                    flag.a = false;
                i++;
                if (flag.a == false)
                {
                    while (input[i])
                    {
                        if (input[i] == ' ')
                        {
                            flag.b = true;
                            break;
                        }
                        if (input[i] != quote)
                        {
                            buffer[j] = input[i];
                            j++;
                        }
                        if (input[i] == quote)
                        {
                            flag.a = true;
                            i++;
                            break;
                        }   
                        i++;
                    }
                    if (flag.a == false)
                    {
                        buffer[j] = quote;
                        j++;
                        if (flag.a == false)
                        {
                            buffer[j] = ' ';
                            j++;
                        }
                        break;
                    }
                }
            }
        }
        else if (input[i] != quote)
        {
            buffer[j] = input[i];
            j++;
        }
        if (input[i] != '\0')
            i++;
    }
    if (flag.a == true)
    {
        write(2,"Unclosed quotes\n", 16);
        return (NULL);
    }
    //printf("%s\n", buffer);
    printf(" BUFFER ----> %s\n", buffer);
    return (buffer);
}