#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../minishell.h"

// Function to create a new AST node
t_ast* createNode(char *value, char *type) {
    t_ast *newNode = (t_ast *)malloc(sizeof(t_ast));
    if (!newNode) 
        exit(1);
    newNode->value = strdup(value);
    newNode->type = strdup(type);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


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

void    assign_node(t_ast *root, char **split, t_index index, bool flag)
{

    if (index.pip <= 0)
        return ;
    index.i = index.pip - 1;
    while (index.i >= 0 && flag == true)
    {
        if (strcmp(split[index.i], "|") == 0)
        {
            root->left = createNode("|", "pipe");
            index.pip_h = index.pip;
            index.pip = index.i;
            assign_node(root->left, split, index, true);
            assign_node(root->left, split, index, false);
            flag = true;
            break;
        }
        else if (strcmp(split[index.i], "<") == 0)
        {
            root->left = createNode(ft_strjoin(split[index.i], split[index.i + 1]), "rein");
            index.pip_h = index.pip;
            index.pip = index.i + 1;
            assign_node(root->left, split, index,true);
            // FIGURE OUT LATER HOW TO ASSIGN COMMAND TO LEFT <file cat or cat <file

            assign_node(root->left, split, index,false); 
            flag = true;
            break;
        }
        index.i-= 1;
    }

    index.i = index.pip + 1;
    while (index.i < index.pip_h && flag != true)
    {
        if (strcmp(split[index.i], ">") == 0)
        {
            root->right = createNode(ft_strjoin(strdup(split[index.i]), split[index.i + 1]), "reout");
            break;
        }
        else
        {
            if (root->right == NULL)
                root->right = createNode(split[index.i], "rein");
            else
            {
                root->right->value = ft_strjoin(root->right->value, split[index.i]);
            }
        }
        index.i+= 1;
        if (index.i == index.pip_h)
        {
            printf("RIGHT %s\n", root->right->value);
            flag = true;
        }
    }
}

t_ast  *divide_and_conquer(char **split, int left, int right, bool flag)
{
    t_index index;
    t_ast *root;

  
    index.i = 0;
    index.pip = right - 1;
    if (left >= right)
        return NULL;
    if (!flag)
    {
        while (index.pip >= left)
        {
            if (strcmp(split[index.pip], "|") == 0)
            {
                root = createNode("|", "pipe");
                break; 
            }
            index.pip--;
        }
    }
    if (index.pip > 0)
    {
        assign_node(root, split, index, true);

        index.pip_h = index.pip;
        //assign_node(root, split, index, false);
        flag = false;
        index.i = index.pip + 1;
        while (index.i <= right && flag != true)
        {
            if (strcmp(split[index.i], ">") == 0)
            {
                if (root->right == NULL)
                {
                    root->right = createNode(ft_strjoin(strdup(split[index.i]), split[index.i + 1]), "reout");
                }
                break;
            }
            else
            {
                if (root->right == NULL)
                    root->right = createNode(split[index.i], "rein");
                else
                {
                    root->right->value = ft_strjoin(root->right->value, split[index.i]);
                }
            }
            index.i+= 1;
            if (index.i == right)
            {
                flag = true;
            }
    }
    }
    else
        return NULL;
    return (root);
}

t_ast* parse_input(char **split)
{
    int i;
    t_ast *root;

    i = 0;
    while (split[i] != NULL)
        i++;
    i--;
    root = divide_and_conquer(split, 0, i, false);
    printf("     %s\n", root->value);
    printf("  %s", root->left->value);
    printf("     %s\n", root->right->value);
    printf("%s   ", root->left->left->value);
    printf("%s   ", root->left->right->value);
    return NULL;

}

int main() {
    char input[] = "< file cat -e | grep pattern | ls > output.txt";
    char **split;
    t_ast *root;
    int n_pipes;

    split = ft_split(input, ' ');
    parse_input(split);

    root = createNode("|", "operator"); // LAST PIPE AS MAIN ROOT ALWAYS;

    root->right = createNode("ls", "cmd");
    root->left = createNode(">", "operator");
    root->left->right = createNode("outfile", "fd");
    root->left->left = createNode("|", "operator");
    root->left->left->right = createNode("awk '{print $1}'", "cmd");
    root->left->left->left = createNode("|", "operator");
    root->left->left->left->right = createNode("grep c", "command");
    root->left->left->left->left = createNode("cat infile", "cmd");
    //recursive_exec(root, &n_pipes);

    return 0;
}
