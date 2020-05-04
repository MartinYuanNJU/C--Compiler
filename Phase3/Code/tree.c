#include "tree.h"

TreeNode *createNode(char *type, char *contents, int linenumber)
{
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    //node->nodetype = nodetype;
    strcpy(node->type, type);
    strcpy(node->contents, contents);
    node->linenumber = linenumber;
    node->parent = NULL;
    node->childrennum = 0;
    node->isleftexp = -1;
    for(int i = 0; i < MAX_CHILDREN_NUM; i++)
        node->children[i] = NULL;
    return node;
}

void addNode(TreeNode *parent, TreeNode *child)
{
    parent->children[parent->childrennum] = child;
    parent->childrennum++;
    if(child != NULL)
        child->parent = parent;
    //parent->children[0]->parent=NULL;
    //parent->linenumber=parent->children[0]->linenumber;
}

void printParsingTree(TreeNode *root, int blankcount)
{
    if(root == NULL)
        return;
    else if(root->childrennum == 0) //terminal token
    {
        for(int i = 0; i < blankcount; i++)
            printf(" ");
        if(strcmp(root->type, "INT") == 0)
            printf("INT: %d", atoi(root->contents));
        else if(strcmp(root->type, "FLOAT") == 0)
            printf("FLOAT: %f", atof(root->contents));
        else if(strcmp(root->type, "TYPE") == 0)
            printf("TYPE: %s", root->contents);
        else if(strcmp(root->type, "ID") == 0)
            printf("ID: %s", root->contents);
        else
            printf("%s", root->type);
        printf("\n");
    }
    else //non-terminal
    {
        for(int i = 0; i < blankcount; i++)
            printf(" ");
        printf("%s (%d)\n", root->contents, root->linenumber);
        for(int i = 0; i < root->childrennum; i++)
            printParsingTree(root->children[i], blankcount+2);
    }
}
