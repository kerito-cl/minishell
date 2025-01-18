#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../minishell.h"

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
t_ast* createNode(char **value, char *type, int left, int right) 
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



void    assign_node(t_ast *root, char **split, t_index index, bool flag)
{
    if (index.pip <= 0)
        return ;
    index.i = index.pip - 1;
    while (index.i >= 0 && flag == true)
    {
        if (strcmp(split[index.i], "|") == 0)
        {
            root->left = createNode(split,"pipe", index.i, index.i);
            index.pip_h = index.pip;
            index.pip = index.i;
            assign_node(root->left, split, index, true);
            index.reout = false;
            index.rein = false;
            assign_node(root->left, split, index, false);
            flag = true;
            break;
        }
        else if (strcmp(split[index.i], "<") == 0)
        {
            root->left = createNode(split,"rein",index.i, index.i + 1);
            index.pip_h = index.pip;
            index.pip = index.i;
            assign_node(root->left, split, index,true);
            index.pip = index.i + 1;
            // FIGURE OUT LATER HOW TO ASSIGN COMMAND TO LEFT <file cat or cat <file
            index.reout = false;
            index.rein = true;
            assign_node(root->left, split, index,false); 
            flag = true;
            break;
        }
        index.i-= 1;
    }

    printf("PIP H IS %d\n", index.pip_h);
    index.i = index.pip_h;
    if (index.rein && !flag)
        root->left = createNode(split, "command", index.pip + 1, index.pip_h - 1);

    while (index.i >= index.pip + 1 && !flag && !index.reout)
    {
        if (strcmp(split[index.i], ">") == 0)
        {
            if (root->right == NULL)
                root->right = createNode(split, "reout", index.i, index.i + 1);
            index.reout = true;
            break;
        }
        index.i-= 1;
    }
    //if (index.rein == true && flag == false)
     //   root->left = createNode(split, "command", index.pip + 1, index.pip_h - 1);
    if (index.reout == true && flag == false && !index.rein)
    {
        index.pip_h = index.i - 1;
        index.reout = false;
        assign_node(root->right, split, index, false);
    }
    else if (index.reout == false && flag == false && !index.rein)
        root->right = createNode(split, "command", index.pip + 1, index.pip_h);
}

t_ast  *divide_and_conquer(char **split, int left, int right, bool flag)
{
    t_index index;
    t_ast *root;

    index.i = 0;
    index.pip = right;
    if (!flag)
    {
        while (index.pip >= left)
        {
            if (strcmp(split[index.pip], "|") == 0)
            {
                root = createNode(split, "pipe", index.pip, index.pip);
                break; 
            }
            index.pip--;
        }
    }
    if (index.pip > 0)
    {
        assign_node(root, split, index, true);
        index.pip_h = right;
        index.reout = false;
        index.rein = false;
        assign_node(root, split, index, false);
    // IF INDEX.I STILL NOT == RIGHT , WE RECALL THIS LOOP
    }
    return (root);
}

t_ast *parse_input(t_ast *root, char **split)
{
    int i;

    i = 0;
    while (split[i] != NULL)
        i++;
    i--;
    root = divide_and_conquer(split, 0, i, false);
    freesplit(split);
    printf("     %s\n", root->value[0]);
    printf("  %s", root->left->value[0]);
    printf("     %s\n", root->right->value[1]);
    printf("     %s\n", root->right->right->value[1]);
    printf("%s ", root->left->left->value[0]);
    printf("%s   ", root->left->left->value[1]);
    printf("   %s \n", root->left->right->value[0]);
    printf("%s   ", root->left->left->left->value[0]);
    return (root);
}

int main() {
    char input[] = "< file cat -e | grep pattern | ls -a > output.txt";
    //char input[] = "< file cat -e > outfile";
    char **split;
    t_ast *root;
    int n_pipes;

    split = ft_split(input, ' ');
    root = parse_input(root, split);
    /*freesplit(root->value);
    free(root->type);
    free(root);*/


    return 0;
}
    /*root = createNode("|", "operator"); // LAST PIPE AS MAIN ROOT ALWAYS;

    root->right = createNode("ls", "cmd");
    root->left = createNode(">", "operator");
    root->left->right = createNode("outfile", "fd");
    root->left->left = createNode("|", "operator");
    root->left->left->right = createNode("awk '{print $1}'", "cmd");
    root->left->left->left = createNode("|", "operator");
    root->left->left->left->right = createNode("grep c", "command");
    root->left->left->left->left = createNode("cat infile", "cmd");*/
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