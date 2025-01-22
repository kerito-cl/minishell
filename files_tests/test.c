/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:08:20 by mquero            #+#    #+#             */
/*   Updated: 2025/01/21 18:32:35 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../minishell.h"

void    assign_to_left(t_ast *root, t_token *tokens, t_index *i, bool flag);

void print_values(char *values) 
{
    if (values) {
            printf("%s", values);
    }
}

void print_ast(t_ast *node, int depth)
{
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("Type: %d, Value: ", node->type);
    print_values(node->value);
    printf("\n");
    if (node->left || node->right) {
        print_ast(node->left, depth + 1);
        print_ast(node->right, depth + 1);
    }
}
// Function to create a new AST node
t_ast* create_node(char *s1 , tokentype type) 
{
    t_ast *new_node = (t_ast *)malloc(sizeof(t_ast));
    size_t  len;

    if (!new_node) 
        exit(1);
    len = 0; 
    if (s1 != NULL)
    {
        len = ft_strlen(s1);
        new_node->value = ft_strndup(s1, len);
    }
    else
        new_node->value = NULL;
    new_node->type = type;
    new_node->left = NULL;
    new_node->right = NULL;
    return (new_node);
}

bool assign_node(t_ast **root, t_token *tokens, t_index *i, int n)
{
    i->key = i->min;
    i->max = i->max;
    while (i->key < i->max)
    {
        if (n == tokens[i->key].type && !tokens[i->key].lock)
        {
            *root = create_node(tokens[i->key + 1].value, n);
            tokens[i->key].lock = true;
            tokens[i->key + 1].lock = true;
            assign_to_left(*root , tokens, i, true);
            return (true);
        }
        i->key++;
    }
    return (false);
}

void    assign_to_right(t_ast *root, t_token *tokens, t_index *i)
{
    if (assign_node(&(root->right), tokens, i, REIN2))
        return ;
    if (assign_node(&(root->right), tokens, i, REIN))
        return ;
    if (assign_node(&(root->right), tokens, i, REOUT))
        return ;
    if (assign_node(&(root->right), tokens, i, REOUT2))
        return ;
    i->key = i->min;
    i->max = i->max;
    while (i->key <= i->max)
    {
        if (ARG == tokens[i->key].type && !tokens[i->key].lock)
        {
            root->right = create_node(tokens[i->key].value, CMD);
            tokens[i->key].lock = true;
            return ;
        }
        i->key++;
    }
}

void    assign_to_left(t_ast *root, t_token *tokens, t_index *i, bool flag)
{
    i->key = i->max - 1;
    while (i->key > i->min)
    {
        if (PIPE == tokens[i->key].type)
        {
            root->left = create_node(NULL, PIPE);
            i->max = i->key;
            assign_to_left(root->left, tokens, i, false);
            i->min = i->key + 1;
            i->max = i->len;
            assign_to_right(root->left, tokens, i);
            return ;
        }
        i->key--;
    }
    if (assign_node(&(root->left), tokens, i, REIN2))
        return ;
    if (assign_node(&(root->left), tokens, i, REIN))
        return ;
    if (assign_node(&(root->left), tokens, i, REOUT))
        return ;
    if (assign_node(&(root->left), tokens, i, REOUT2))
        return ;
    i->key = i->min;
    while (i->key < i->max)
    {
        if (ARG == tokens[i->key].type && !tokens[i->key].lock)
        {
            if (!flag)
                root->left = create_node(tokens[i->key].value, CMD);
            else
                root->right = create_node(tokens[i->key].value, CMD);
            tokens[i->key].lock = true;
            return ;
        }
        i->key++;
    }
}

void    find_root(t_ast **root, t_token *tokens, t_index *i) 
{
    if (assign_node(root, tokens, i, REIN2))
        return ;
    if (assign_node(root, tokens, i, REIN))
        return ;
    if (assign_node(root, tokens, i, REOUT))
        return ;
    if (assign_node(root, tokens, i, REOUT2))
        return ;
    i->key = i->min;
    while (i->key <= i->max)
    {
        if (ARG == tokens[i->key].type && !tokens[i->key].lock)
        {
            *root = create_node(tokens[i->key].value, CMD);
            tokens[i->key].lock = true;
            return ;
        }
        i->key++;
    }
}

t_ast  *divide_input(t_token *tokens, int len, t_index *i, bool flag)
{
    t_ast *root;

    while (i->pip > 0)
    {
        if (tokens[i->pip].type == PIPE)
        {
            root = create_node(NULL, PIPE);
            break;
        }
        i->pip--;
    }
    if (i->pip > 0)
    {
        i->max = i->pip;
        i->len = i->pip;
        assign_to_left(root, tokens, i, false);
        i->min = i->pip + 1;
        i->max = len ;
        assign_to_right(root, tokens, i);
    }
    else
        find_root(&root, tokens, i);
    return (root);
}
t_ast *parse_input(t_ast *root, t_token *tokens, int len)
{
    t_index i;

    i.pip = len + 1;
    i.min = 0;
    i.len = len;
    i.max = i.len ;
    root = divide_input(tokens, len, &i, false);
    print_ast(root, 0);
   return (root);
}

bool compare_token(char *input, int *i, bool flag)
{
    if (input[*i] == '<' || input[*i] == '>')
    {
        *i -= 1;
        return (false);
    }
    if (input[*i] == '|' )
    {
        *i -= 1;
        return (false);
    }
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
        if (input[i] == ' ')
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

int main() 
{
    t_token *tokens;
    t_ast *root;
    int len;
    char input[] = "grep c| ls";

    //char input[] = "< in cat > out";


    tokens = (t_token *)malloc(sizeof(t_token) * ft_strlen(input) + 1);
    len = tokenize(tokens, input);
    int i = 0;
    /*while (i <= len)
    {
        if (tokens[i].value != NULL)
            printf("%s\n", tokens[i].value);
        i++;
    }*/
    root = parse_input(root, tokens, len);

    return 0;

}















    //char input[] = "< das cat text -e | ls > out";
    //char input[] = "< das cat | > out";
    //char input[] = "cat | ls > out";
    //char input[] = "< das cat text -e | ls > out1 > out2";
    //char input[] = "< in1 < int2 cat text -e | ls > out1 > out2";
    //char input[] = "< in1 < int2 cat text";
    //char **split;


    //root = parse_input(root, input);
    /*freesplit(root->value);
    free(root->type);
    free(root);*/


    /*root = create_node("|", "operator"); // LAST PIPE AS MAIN ROOT ALWAYS;

    root->right = create_node("ls", "cmd");
    root->left = create_node(">", "operator");
    root->left->right = create_node("outfile", "fd");
    root->left->left = create_node("|", "operator");
    root->left->left->right = create_node("awk '{print $1}'", "cmd");
    root->left->left->left = create_node("|", "operator");
    root->left->left->left->right = create_node("grep c", "command");
    root->left->left->left->left = create_node("cat infile", "cmd");*/
    //recursive_exec(root, &n_pipes);

//execute recursively pipes according to node->type and node->value
/*void recursive_exec(ASTNode *node, int *n_pipes) {

    if (node == NULL) return;
    if (ft_strcmp(node->value, "|") == 0)
    {
        / CHILD PROCESS LEFT
        pid1 = fork();
        if (pid == 0)
            childfunctions(t_ast *root->left)
        pid2 = fork();
        if (pid == 0)
            childfunctions(t_ast *root->right)
        waitpid
        waitpid
        /
    }
    else{
        
            pid1 = fork()
            if (pid == 0)
                childfunctions(t_ast *root->left)
            waitpid
          
    }
}*/