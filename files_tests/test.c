/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:08:20 by mquero            #+#    #+#             */
/*   Updated: 2025/01/20 21:42:00 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../minishell.h"

//void    assign_node(t_ast *root, char **split, t_index index, bool flag);


void    assign_node(t_ast **root, t_token *tokens, t_index *i ,int used);

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

char    **assign_value(char **split, int left, int right)
{
    int i;
    int len;
    char    **value;

    len = (right - left) + 1;
    value = (char **)malloc(sizeof(char *) * (len + 1));
    if (value == NULL)
        return (NULL);
    value[len] = NULL;
    i = 0;
    while(left <= right)
    {
        value[i] = (char *)malloc(sizeof(char) * ft_strlen(split[left]) + 2);
        if (value[i] == NULL)
        {
            freesplit(value);
            return (NULL);
        }
        ft_strlcpy(value[i], split[left], ft_strlen(split[left]) + 1);
        i++;
        left++;
    }
    return (value);
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
    return new_node;
}
/*
void    find_root(t_ast **root, char **split, t_index *index)
{
    index->i = 0;
    while (index->i <= index->pip_h)
    {
        if (ft_strcmp(split[index->i], "<") == 0 && root == NULL)
            *root = create_node(split, "rein", index->i , index->i + 1);
        if (ft_strcmp(split[index->i], "<<") == 0 && root == NULL)
            *root = create_node(split, "rein2", index->i , index->i + 1);
        if (ft_strcmp(split[index->i], ">") == 0 && root == NULL)
            *root = create_node(split, "reout", index->i, index->i + 1);
        if (ft_strcmp(split[index->i], ">>") == 0 && root == NULL)
            *root = create_node(split, "reout2", index->i, index->i + 1);
        if (root != NULL)
        {
            index->pip_h = index->pip;
            break;
        }
        index->i++;
    }
    if (root == NULL)
        *root = create_node(split, "reout2", 0, index->pip_h);
}
bool    find_pipe(t_ast *root, char **split, t_index index)
{
    if (ft_strcmp(split[index.i], "|") == 0)
    {
        root->left = create_node(split,"pipe", index.i, index.i);
        index.pip_h = index.pip;
        index.pip = index.i;
        assign_node(root->left, split, index, true);
        index.reout = false;
        index.rein = false;
        assign_node(root->left, split, index, false);
        return (false);
    }
    return (true);
}

bool    find_operators_left(t_ast *root, char **split, t_index index)
{
    while (index.i < index.pip_h)
    {
        if (ft_strcmp(split[index.i], "<") == 0)
        {
            root->left = create_node(split,"rein",index.i, index.i + 1);
            index.pip_h = index.pip - 1;
            index.pip = index.i + 1;
            index.reout = false;
            index.rein = true;
            assign_node(root->left, split, index,false); 
            return (false);
        }
        else if (ft_strcmp(split[index.i], ">") == 0)
        {
            root->left = create_node(split,"reout",index.i, index.i + 1);
            index.pip = -1;
            index.pip_h = index.i - 1;
            assign_node(root->left, split, index,false); 
            return (false);
        }
        index.i++;
    }
    return (true);
}
bool    find_operators_r1(t_ast *root, char **split, t_index index, bool flag)
{
    while (index.i < index.pip_h  && !flag && !index.reout)
    {
        if (ft_strcmp(split[index.i], "<") == 0)
        {
            root->right = create_node(split,"rein",index.i, index.i + 1);
            index.pip = index.i + 1;
            index.reout = false;
            index.rein = true;
            assign_node(root->right, split, index,false); 
            return (false);
        }
        index.i++;
    }
    return (true);
}

bool    find_operators_r2(t_ast *root, char **split, t_index index, bool flag)
{
    while (index.i >= index.pip + 1 && !flag)
    {
        if (ft_strcmp(split[index.i], ">") == 0 && !index.rein)
        {
            root->right = create_node(split, "reout", index.i, index.i + 1);
            index.reout = true;
            index.pip_h = index.i - 1;
            assign_node(root->right, split, index, false);
            return (false);
        }
        else if (ft_strcmp(split[index.i], ">") == 0 && index.rein)
        {
            root->left = create_node(split, "reout", index.i, index.i + 1);
            index.pip_h = index.i - 1;
            break;
        }
        index.i-= 1;
    }
    if (!flag && index.pip + 1 <= index.pip_h)
        root->right = create_node(split, "command", index.pip + 1, index.pip_h);
    else if (flag && index.pip + 1 <= index.pip_h)
        root->left = create_node(split, "command", index.pip + 1, index.pip_h);
    return (true);
}

void     assign_ifnopipe(t_ast *root ,char **split, t_index index)
{
    index.i = index.pip;
    while (index.i < index.pip_h )
    {
        if (ft_strcmp(split[index.i], "<") == 0 && !index.rein)
        {
            root->left = create_node(split,"rein",index.i, index.i + 1);
            index.pip = index.i + 1;
            index.reout = false;
            index.rein = true;
            assign_ifnopipe(root, split, index); 
            return ;
        }
        index.i++;
    }
    index.i = index.pip_h;
    while (index.i >= index.pip && !index.reout)
    {
        if (ft_strcmp(split[index.i], ">") == 0 && !index.rein)
        {
            root->left = create_node(split, "reout", index.i, index.i + 1);
            index.reout = true;
            break;
        }
        else if (ft_strcmp(split[index.i], ">") == 0 && index.rein)
        {
            root->left = create_node(split, "reout", index.i, index.i + 1);
            index.pip_h = index.i - 1;
            index.reout = false;
            break;
        }
        index.i-= 1;
    }
    if (index.reout == true && !index.rein)
    {
        index.pip_h = index.i - 1;
        index.reout = false;
        assign_ifnopipe(root, split, index);
    }
    else if (index.reout == false)
    {
        if (root == NULL)
            root = create_node(split, "command", 0 , index.pip_h);
        else
            root->right = create_node(split, "command", index.pip + 1, index.pip_h);
    }
}

void    assign_node(t_ast *root, char **split, t_index index, bool flag)
{
    if (index.pip <= 0 && flag)
        return ;
    index.i = index.pip - 1;
    while (index.i >= 0 && flag == true)
    {
        if (!find_pipe(root, split, index))
            return ;
        if (index.i != 0)
            index.i-= 1;
        if (index.i == 0)
        {
            index.pip_h = index.pip - 1;
            if (!find_operators_left(root, split, index))
                return ;
            index.pip = -1;
            break;
         }
    }
    index.i = index.pip + 1;
    if (!find_operators_r1(root, split, index, flag))
        return ;
    index.i = index.pip_h;
    if (!find_operators_r2(root, split, index, flag))
        return ;
}

t_ast  *divide_input(char **split, int right, bool flag)
{
    t_index index;
    t_ast *root;

    index.i = 0;
    index.pip = right;
    index.pip_h = right;
    index.reout = false;
    index.rein = false;
    root = NULL;
    if (!flag)
    {
        while (index.pip > 0)
        {
            if (ft_strcmp(split[index.pip], "|") == 0)
            {
                root = create_node(split, "pipe", index.pip, index.pip);
                break; 
            }
            index.pip--;
        }
    }
    if (index.pip > 0)
    {
        assign_node(root, split, index, true);
        assign_node(root, split, index, false);
    }
    else
    {
        find_root(&root, split, &index);
        assign_ifnopipe(root,split,index);
    }
    return (root);
}

t_ast *parse_input(t_ast *root, char *input)
{
    int i;
    char **split;

    split = ft_split(input, ' ');
    i = 0;
    while (split[i] != NULL)
        i++;
    i--;
    root = divide_input(split, i, false);
    freesplit(split);
    print_ast(root, 0);
    //printf("%s \n", root->value[0]);
    //printf("%s \n", root->left->value[0]);
    return (root);
}
*/

void    assign_to_left(t_ast *root, t_token *tokens, t_index i, int used)
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
            assign_to_left(root->left, tokens, i, k);
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
            assign_to_left(root->left, tokens, i , k); 
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
            assign_to_left(root->left, tokens, i , k); 
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
            assign_to_left(root->left, tokens, i , k); 
            return ;
        }
        k++;
    }
    k = i.min;
    while (k < i.max)
    {
        if (ARG == tokens[k].type && !tokens[k].lock)
        {
            if (root == NULL)
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
    i.prior = 0;
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
    assign_to_left(root, tokens, i , -1);
    return root;
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
    if (input[i] == '|' || input[i] == ' ')
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
    while (input[i])
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
            while (input[i])
            {
                if (!compare_token(input, i))
                {
                    tokens[j].value = ft_strdup(input + k , (size_t)i - k);
                    tokens[j].type = ARG;
                    break;
                }
                i++;
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
    char input[] = "cat -e Makefile <in << s > out | grep c | ls >out";


    tokens = (t_token *)malloc(sizeof(t_token) * ft_strlen(input) + 1);
    len = tokenize(tokens, input);
    int i = 0;
    while (i < len)
    {
        i++;
    }
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