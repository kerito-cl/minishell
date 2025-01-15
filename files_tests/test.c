#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct ASTNode {
    char *value;         // The value of the node (e.g., command or operator)
    char *type;         // The value of the node (e.g., command or operator)
    struct ASTNode *left;  // Left child (usually for arguments or commands)
    struct ASTNode *right; // Right child (usually for subsequent commands or files)
} ASTNode;

// Function to create a new AST node
ASTNode* createNode(char *value, char *type) {
    ASTNode *newNode = (ASTNode *)malloc(sizeof(ASTNode));
    if (!newNode) 
        exit(1);
    newNode->value = strdup(value);
    newNode->type = strdup(type);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


//execute recursively pipes according to node->type and node->value
void recursive_exec(ASTNode *node, int *n_pipes) {

    if (node == NULL) return;
    if (node->value[0] == '|')
    {
        *n_pipes += 1;
        recursive_exec(node->left, n_pipes);
        *n_pipes -= 1;
    }
    else{
        recursive_exec(node->left, n_pipes);
    }
    printf("%d ", *n_pipes);
    printf("%s ", node->value);
    /*
        if (node->type == cmd)
            CHILD  PROCESS EXEC LEFT
    */
    recursive_exec(node->right, n_pipes);
    /*
        if (node->type == cmd)
            CHILD  PROCESS EXEC RIGHT
    */
}

int main() {
    char input[] = "cat file | grep pattern > output.txt";
    ASTNode *root;
    ASTNode *current;
    ASTNode *temp;
    int n_pipes;

    root = createNode("|", "operator");
    root->right = createNode("ls", "cmd");
    root->left = createNode(">", "operator");
    root->left->right = createNode("outfile", "fd");
    root->left->left = createNode("|", "operator");
    root->left->left->right = createNode("awk '{print $1}'", "cmd");
    root->left->left->left = createNode("|", "operator");
    root->left->left->left->right = createNode("grep c", "command");
    root->left->left->left->left = createNode("cat infile", "cmd");
    recursive_exec(root, &n_pipes);

    return 0;
}
