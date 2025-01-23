/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:49:00 by mquero            #+#    #+#             */
/*   Updated: 2025/01/23 17:45:37 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


char  *deal_with_quotes(char *input)
{
    int i;
    int j;
    int k;
    bool flag;
    char *buffer;
    char  quote;

    k = 0;
    i = 0;
    j = 0;
    flag = false;
    buffer = (char *)malloc(sizeof(char) * ft_strlen(input) * 2);
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
                flag = true;
                quote = '\'';
                break;
            }
            if (input[k] == '\"')
            {
                flag = true;
                quote = '\"';
                break;
            }   
            if (input[k] == ' ')
               break;
            k++;
        }
        if (flag)
        {
            buffer[j] = '\'';
            j++;
            while (input[i])
            {
                if (input[i] != quote)
                {
                    buffer[j] = input[i];
                    j++;
                }
                else if (input[i] == quote && i != k)
                    flag = false;
                i++;
                if (flag == false)
                {
                    while (input[i])
                    {
                        if (input[i] != quote)
                        {
                            buffer[j] = input[i];
                            j++;
                        }
                        if (input[i] == quote)
                        {
                            flag = true;
                            i++;
                            break;
                        }   
                        if (input[i] == ' ')
                        break;
                        i++;
                    }
                    if (flag == false)
                    {
                        buffer[j] = '\'';
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
    if (flag == true)
    {
        write(2,"Unclosed quotes\n", 16);
        exit(1);
    }
    printf("%s\n", buffer);
    return (buffer);
}