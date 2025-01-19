/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mquero <mquero@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:08:20 by mquero            #+#    #+#             */
/*   Updated: 2025/01/19 21:02:23 by mquero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../minishell.h"

void print_values(char **values) {
    if (values) {
        for (int i = 0; values[i] != NULL; i++) {
            printf("%s", values[i]);
            if (values[i + 1] != NULL) {
                printf(", ");
            }
        }
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
    printf("Type: %s, Value: ", node->type);
    print_values(node->value);
    printf("\n");
    if (node->left || node->right) {
        print_ast(node->left, depth + 1);
        print_ast(node->right, depth + 1);
    }
}

void    assign_node(t_ast *root, char **split, t_index index, bool flag);

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
t_ast* create_node(char **value, char *type, int left, int right) 
{
    t_ast *newNode = (t_ast *)malloc(sizeof(t_ast));
    if (!newNode) 
        exit(1);
    newNode->value = assign_value(value, left, right);
    newNode->type = strdup(type);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bool    find_pipe(t_ast *root, char **split, t_index index)
{
    if (strcmp(split[index.i], "|") == 0)
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
        if (strcmp(split[index.i], "<") == 0)
        {
            root->left = create_node(split,"rein",index.i, index.i + 1);
            index.pip_h = index.pip - 1;
            index.pip = index.i + 1;
            index.reout = false;
            index.rein = true;
            assign_node(root->left, split, index,false); 
            return (false);
        }
        else if (strcmp(split[index.i], ">") == 0)
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
    while (index.i < index.pip_h && !index.rein && !flag && !index.reout)
    {
        if (strcmp(split[index.i], "<") == 0)
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
    while (index.i >= index.pip + 1 && !flag && !index.reout)
    {
        if (strcmp(split[index.i], ">") == 0 && !index.rein)
        {
            root->right = create_node(split, "reout", index.i, index.i + 1);
            index.reout = true;
            index.pip_h = index.i - 1;
            assign_node(root->right, split, index, false);
            return (false);
        }
        else if (strcmp(split[index.i], ">") == 0 && index.rein)
        {
            root->left = create_node(split, "reout", index.i, index.i + 1);
            index.pip_h = index.i - 1;
            break;
        }
        index.i-= 1;
    }
    if (!flag)
        root->right = create_node(split, "command", index.pip + 1, index.pip_h);
    else if (flag)
    {
        root->left = create_node(split, "command", index.pip + 1, index.pip_h);
    }
    return (true);
}

void     assign_ifnopipe(t_ast **root ,char **split, t_index index)
{
    index.i = 0;
    while (index.i < index.pip_h && !index.rein)
    {
        if (strcmp(split[index.i], "<") == 0)
        {
            *root = create_node(split,"rein",index.i, index.i + 1);
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
        if (strcmp(split[index.i], ">") == 0 && !index.rein)
        {
            (*root) = create_node(split, "reout", index.i, index.i + 1);
            index.reout = true;
            break;
        }
        else if (strcmp(split[index.i], ">") == 0 && index.rein)
        {
            (*root)->left = create_node(split, "reout", index.i, index.i + 1);
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
        if ((*root) == NULL)
            (*root) = create_node(split, "command", 0 , index.pip_h);
        else
            (*root)->right = create_node(split, "command", index.pip + 1, index.pip_h);
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
            if (strcmp(split[index.pip], "|") == 0)
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
        assign_ifnopipe(&root,split,index);
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

int main() 
{
    //char input[] = "< file cat -e > out1 | < in2 grep pattern > out2 | ls -a > output.txt";
    //char input[] = "< das cat text -e | ls > out";
    //char input[] = "cat | ls > out";
    char input[] = "< das cat text -e | ls > out";
    //char **split;
    t_ast *root;
    int n_pipes;

    root = parse_input(root, input);
    /*freesplit(root->value);
    free(root->type);
    free(root);*/


    return 0;
}
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
    if (strcmp(node->value, "|") == 0)
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