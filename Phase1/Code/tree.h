#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 33
#define MAX_CHILDREN_NUM 7

//typedef enum NodeType {intvalue, floatvalue, valuetype, identifier, symboltoken, keytoken, nonterminal} NodeType;

/*
intvalue: 234, 45
floatvalue: 35.789
valuetype: int, float
identifier: num, a
symboltoken: +, -, *, /, =, ==, <=, (, [, {
keytoken: while, if, return
nonterminal: ExtDefList, VarList
*/

typedef struct TreeNode
{
    //NodeType nodetype;
    char type[MAX_LENGTH];
    char contents[MAX_LENGTH];
    int linenumber;
    struct TreeNode *parent;
    int childrennum;
    struct TreeNode *children[MAX_CHILDREN_NUM];

} TreeNode;

TreeNode *createNode(char *type, char *contents, int linenumber);

void addNode(TreeNode *parent, TreeNode *child);

void printParsingTree(TreeNode *root, int blankcount);

#endif