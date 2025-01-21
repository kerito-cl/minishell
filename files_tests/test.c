/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:08:20 by mquero            #+#    #+#             */
/*   Updated: 2025/01/21 11:02:44 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../minishell.h"

void    assign_to_left(t_ast *root, t_token *tokens, t_index i, bool flag);


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
        new_node->value = ft_strdup(s1, len);
    }
    else
        new_node->value = NULL;
    new_node->type = type;
    new_node->left = NULL;
    new_node->right = NULL;
    return (new_node);
}

void    assign_to_right(t_ast *root, t_token *tokens, t_index i, bool flag)
{
    int k;

    k = i.min;
    while (k < i.max)
    {
        if (REIN2 == tokens[k].type && !tokens[k].lock)
        {
            root->right = create_node(tokens[k + 1].value, REIN2);
            tokens[k].lock = true;
            tokens[k + 1].lock = true;
            assign_to_left(root->right, tokens, i, true);
            return ;
        }
        k++;
    }
    k = i.min;
    while (k < i.max)
    {
        if (REIN == tokens[k].type && !tokens[k].lock)
        {
            root->right = create_node(tokens[k + 1].value, REIN);
            tokens[k].lock = true;
            tokens[k + 1].lock = true;
            assign_to_left(root->right, tokens, i, true);
            return ;
        }
        k++;
    }
    k = i.min;
    while (k < i.max)
    {
        if (REOUT == tokens[k].type && !tokens[k].lock)
        {
            root->right = create_node(tokens[k + 1].value, REOUT);
            tokens[k].lock = true;
            tokens[k + 1].lock = true;
            assign_to_left(root->right, tokens, i, true);
            return ;
        }
        k++;
    }
    k = i.min;
    while (k < i.max)
    {
        if (ARG == tokens[k].type && !tokens[k].lock)
        {
            root->right = create_node(tokens[k].value, ARG);
            tokens[k].lock = true;
            return ;
        }
        k++;
    }
}
void    assign_to_left(t_ast *root, t_token *tokens, t_index i, bool flag)
{
    int k;
    int prior;

    k = i.max - 1;
    while (k > i.min)
    {
        if (PIPE == tokens[k].type)
        {
            root->left = create_node(NULL, PIPE);
            i.max = k;
            assign_to_left(root->left, tokens, i, false);
            i.min = k + 1;
            i.max = i.len;
            assign_to_right(root->left, tokens, i, false);
            return ;
        }
        k--;
    }
    k = i.min;
    while (k < i.max)
    {
        if (REIN2 == tokens[k].type && !tokens[k].lock)
        {
            root->left = create_node(tokens[k + 1].value, REIN2);
            tokens[k].lock = true;
            tokens[k + 1].lock = true;
            assign_to_left(root->left, tokens, i, true);
            return ;
        }
        k++;
    }
    k = i.min;
    while (k < i.max)
    {
        if (REIN == tokens[k].type && !tokens[k].lock)
        {
            root->left = create_node(tokens[k + 1].value, REIN);
            tokens[k].lock = true;
            tokens[k + 1].lock = true;
            assign_to_left(root->left, tokens, i, true);
            return ;
        }
        k++;
    }
    k = i.min;
    while (k < i.max)
    {
        if (REOUT == tokens[k].type && !tokens[k].lock)
        {
            root->left = create_node(tokens[k + 1].value, REOUT);
            tokens[k].lock = true;
            tokens[k + 1].lock = true;
            assign_to_left(root->left, tokens, i, true);
            return ;
        }
        k++;
    }
    k = i.min;
    while (k < i.max)
    {
        if (ARG == tokens[k].type && !tokens[k].lock)
        {
            if (!flag)
                root->left = create_node(tokens[k].value, ARG);
            else
                root->right = create_node(tokens[k].value, ARG);
            tokens[k].lock = true;
            return ;
        }
        k++;
    }
}

t_ast  *divide_input(t_token *tokens, int len, bool flag)
{
    t_ast *root;
    t_index i;

    i.pip = len;
    while (i.pip > 0)
    {
        if (tokens[i.pip].type == PIPE)
        {
            root = create_node(NULL, PIPE);
            break;
        }
        i.pip--;
    }
    i.min = 0;
    i.max = i.pip;
    i.len = i.pip;
    assign_to_left(root, tokens, i, false);
    i.min = i.pip + 1;
    i.max = len;
    assign_to_right(root, tokens, i, false);
    return (root);
}
t_ast *parse_input(t_ast *root, t_token *tokens, int len)
{
   root = divide_input(tokens, len, false);
   print_ast(root, 0);
   /*printf("%d\n", root->left->type);
   printf("%s\n", root->left->left->value);
   printf("%d\n", root->left->left->type);
   printf("%s\n", root->left->left->left->value);*/
   return (root);
}

bool compare_token(char *input, int i)
{
    if (input[i] == '<' || input[i] == '>')
        return (false);
    if (input[i] == '|' || input[i] == ' ' )
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
    k = 0;
    flag = true;
    while (input[i] != '\0')
    {
        if (input[i] == ' ')
            i++;
        if (input[i] == '<' && input[i + 1] != '<')
            tokens[j].type = REIN;
        else if (input[i] == '<' && input[i + 1] == '<')
        {
            tokens[j].type = REIN2;
            i++;
        }
        else if (input[i] == '>' && input[i + 1] != '>')
            tokens[j].type = REOUT;
        else if (input[i] == '>' && input[i + 1] == '>')
        {
            tokens[j].type = REOUT2;
            i++;
        }
        else if (input[i] == '|')
            tokens[j].type = PIPE;
        else 
        {
            k = i;
            while (input[i] != '\0')
            {
                if (!compare_token(input, i))
                {
                    tokens[j].value = ft_strdup(input + k , (size_t)i - k);
                    tokens[j].type = ARG;
                    printf("%s\n", tokens[j].value);
                    break;
                }
                i++;
            }
            if (input[i] == '\0')
            {
                tokens[j].value = ft_strdup(input + k , (size_t)i - k);
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
    char input[] = "cat | < in grep c > out1 >out2 | ls >out3";


    tokens = (t_token *)malloc(sizeof(t_token) * ft_strlen(input) + 1);
    len = tokenize(tokens, input);
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