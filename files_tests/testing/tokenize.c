/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:15:29 by mquero            #+#    #+#             */
/*   Updated: 2025/01/22 17:41:58 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool add_type(t_token *tokens, char *input, int *i, int j)
{
    if (input[*i] == '<' && input[*i + 1] != '<')
    {
        tokens[j].type = REIN;
        return (true);
    }
    else if (input[*i] == '<' && input[*i + 1] == '<')
    {
        tokens[j].type = REIN2;
        *i+=1;
        return (true);
    }
    else if (input[*i] == '>' && input[*i + 1] != '>')
    {
        tokens[j].type = REOUT;
        return (true);
    }
    else if (input[*i] == '>' && input[*i + 1] == '>')
    {
        tokens[j].type = REOUT2;
        *i+=1;
        return (true);
    }
    return (false);
}

bool compare_token(char *input, int i, bool flag)
{
    if (input[i] == '<' || input[i] == '>')
        return (false);
    if (input[i] == '|' )
        return (false);
    if (input[i] == ' ' && flag == true)
        return (false);
    return (true);
}

bool add_redirval(t_token *tokens, char *input, int *i, int j)
{
    int k;

    k = *i;
    while (input[*i] != '\0')
    {
        if (!compare_token(input, *i, true))
        {
            tokens[j].value = ft_strndup(input + k , (size_t)(*i - k));
            tokens[j].type = ARG;
            *i -= 1;
            return (true);
        }
        *i += 1;
    }
    if (input[*i] == '\0')
    {
        tokens[j].value = ft_strndup(input + k , (size_t)(*i - k));
        tokens[j].type = ARG;
        return (false);
    }
    return (false);
}

bool add_cmd(t_token *tokens, char *input, int *i, int j)
{
    int k;

    k = *i;
    while (input[*i] != '\0')
    {
        if (!compare_token(input, *i, false))
        {
            tokens[j].value = ft_strndup(input + k , (size_t)(*i - k));
            tokens[j].type = ARG;
            *i -= 1;
            return (true);
        }
        *i += 1;
    }
    if (input[*i] == '\0')
    {
        tokens[j].value = ft_strndup(input + k , (size_t)(*i - k));
        tokens[j].type = ARG;
        return (false);
    }
    return (false);
}

void deal_with_quotes(char *input)
{
    int i;
    int j;
    bool flag;
    char buffer[1000];

    i = 0;
    j = 0;
    ft_bzero(buffer, 1000);
    while (input[i])
    {
        while (input[i] == '<')
        {
            buffer[j] = input[i];
            j++;
            i++;
        }
        if (input[i] == '\'')
        {
            buffer[j] = input[i];
            j++;
            i++;
            flag = true;
            while (input[i])
            {
                if (input[i] != '\'')
                {
                    buffer[j] = input[i];
                    j++;
                }
                if (input[i] == '\'')
                    flag = false;
                i++;
                if (input[i] == ' ' && flag == false)
                    break;
            }
            buffer[j] = '\'';
            j++;
        }
        else
        {
            buffer[j] = input[i];
            i++;
            j++;
        }
    }
    if (flag == true)
    {
        perror("dssda");
    }
    printf("%s\n", buffer);
}

int tokenize(t_token *tokens, char *input)
{
    int i;
    int j;
    bool flag;

    i = 0;
    j = 0;
    flag = false;
    deal_with_quotes(input);
    while (input[i] != '\0')
    {
        while (input[i] == ' ')
            i++;
        if (add_type(tokens, input, &i, j))
            flag = true;
        else if (input[i] == '|')
            tokens[j].type = PIPE;
        else if (flag == true)
        {
            if (!add_redirval(tokens, input, &i, j))
                break;
            flag = false;
        }
        else if (flag == false)
        {
            if (!add_cmd(tokens, input, &i, j))
                break;
        }
        i++;
        j++;
    }
    return (j);
}