/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:15:29 by mquero            #+#    #+#             */
/*   Updated: 2025/01/25 16:07:00 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool add_type(t_token *tokens, char *buffer, int *i, int j)
{
    if (buffer[*i] == '<' && buffer[*i + 1] != '<')
    {
        tokens[j].type = REIN;
        return (true);
    }
    else if (buffer[*i] == '<' && buffer[*i + 1] == '<')
    {
        tokens[j].type = REIN2;
        *i+=1;
        return (true);
    }
    else if (buffer[*i] == '>' && buffer[*i + 1] != '>')
    {
        tokens[j].type = REOUT;
        return (true);
    }
    else if (buffer[*i] == '>' && buffer[*i + 1] == '>')
    {
        tokens[j].type = REOUT2;
        *i+=1;
        return (true);
    }
    return (false);
}

bool compare_token(char *buffer, int i, bool flag, char quote)
{
    if (quote == 0)
    {
        if (buffer[i] == '<' || buffer[i] == '>')
            return (false);
        if (buffer[i] == '|' )
            return (false);
        if (buffer[i] == ' ' && flag == true)
            return (false);
    }
    return (true);
}

bool add_redirval(t_token *tokens, char *buffer, int *i, int j)
{
    int k;

    k = *i;
    while (buffer[*i] != '\0')
    {
        if (!compare_token(buffer, *i, true, tokens[j].quote))
        {
            tokens[j].value = ft_strndup(buffer + k , (size_t)(*i - k));
            if (!tokens[j].value)
                free_tokens(tokens, j);
            tokens[j].cmd = create_cmd(tokens[j].value);
            tokens[j].type = ARG;
            *i -= 1;
            return (true);
        }
        *i += 1;
    }
    tokens[j].value = ft_strndup(buffer + k , (size_t)(*i - k));
    tokens[j].cmd = create_cmd(tokens[j].value);
    tokens[j].type = ARG;
    return (false);
}

bool add_cmd(t_token *tokens, char *buffer, int *i, int j)
{
    int k;

    k = *i;
    while (buffer[*i] != '\0')
    {
        if (!compare_token(buffer, *i, false, tokens[j].quote))
        {
            tokens[j].value = ft_strndup(buffer + k , (size_t)(*i - k));
            if (!tokens[j].value)
                free_tokens(tokens, j);
            tokens[j].cmd = create_cmd(tokens[j].value);
            tokens[j].type = ARG;
            *i -= 1;
            return (true);
        }
        if (buffer[*i] == tokens[j].quote && *i != k)
            tokens[j].quote = 0;
        *i += 1;
    }
    tokens[j].value = ft_strndup(buffer + k , (size_t)(*i - k));
    tokens[j].cmd = create_cmd(tokens[j].value);
    tokens[j].type = ARG;
    return (false);
}

int tokenize(t_token *tokens, char *input)
{
    int i;
    int j;
    bool flag;
    char    *buffer;

    i = 0;
    j = 0;
    flag = false;
    buffer = deal_with_quotes(input);
    if (!buffer)
        return(-1);
    free(input);
    while (buffer[i] != '\0')
    {
        tokens[j].quote = 0;
        while (buffer[i] == ' ')
            i++;
        if (add_type(tokens, buffer, &i, j))
            flag = true;
        else if (buffer[i] == '|')
            tokens[j].type = PIPE;
        else if (flag == true)
        {
            if (buffer[i] == '\'' || buffer[i] == '\"')
                tokens[j].quote = buffer[i];
            if (!add_redirval(tokens, buffer, &i, j))
                break;
            flag = false;
        }
        else if (flag == false)
        {
            if (buffer[i] == '\'' || buffer[i] == '\"')
                tokens[j].quote = buffer[i];
            if (!add_cmd(tokens, buffer, &i, j))
                break;
        }
        i++;
        j++;
    }
    free(buffer);
    return (j);
}