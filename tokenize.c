/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:15:29 by mquero            #+#    #+#             */
/*   Updated: 2025/01/21 18:37:44 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool compare_token(char *input, int *i, bool flag)
{
    if (input[*i] == '<' || input[*i] == '>')
        return (false);
    if (input[*i] == '|' )
        return (false);
    if (input[*i] == ' ' && flag == true)
        return (false);
    return (true);
}
int tokenize(t_token *tokens, char *input)
{
    int i;
    int j;
    int k;
    bool flag;

    i = 0;
    j = 0;
    flag = false;
    while (input[i] != '\0')
    {
        while (input[i] == ' ')
            i++;
        if (input[i] == '<' && input[i + 1] != '<')
        {
            tokens[j].type = REIN;
            flag = true;
        }
        else if (input[i] == '<' && input[i + 1] == '<')
        {
            tokens[j].type = REIN2;
            flag = true;
            i++;
        }
        else if (input[i] == '>' && input[i + 1] != '>')
        {
            tokens[j].type = REOUT;
            flag = true;
        }
        else if (input[i] == '>' && input[i + 1] == '>')
        {
            tokens[j].type = REOUT2;
            flag = true;
            i++;
        }
        else if (input[i] == '|')
            tokens[j].type = PIPE;
        else if (flag == true)
        {
            k = i;
            while (input[i] != '\0')
            {
                if (!compare_token(input, &i, flag))
                {
                    tokens[j].value = ft_strndup(input + k , (size_t)i - k);
                    tokens[j].type = ARG;
                    flag = false;
                    break;
                }
                i++;
            }
            if (input[i] == '\0')
            {
                tokens[j].value = ft_strndup(input + k , (size_t)i - k);
                tokens[j].type = ARG;
                i -= 1;
                break;
            }
        }
        else if (flag == false)
        {
            k = i;
            while (input[i] != '\0')
            {
                if (!compare_token(input, &i, flag))
                {
                    tokens[j].value = ft_strndup(input + k , (size_t)i - k);
                    tokens[j].type = ARG;
                    i -= 1;
                    break;
                }
                i++;
            }
            if (input[i] == '\0')
            {
                tokens[j].value = ft_strndup(input + k , (size_t)i - k);
                tokens[j].type = ARG;
                break;
            }
        }
        i++; 
        j++;
    }
    return (j);
}