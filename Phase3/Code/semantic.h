#ifndef _SEMANTIC_H_
#define _SEMANTIC_H_

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#define HASH_NUMBER 0x3FFF
#define TYPE_INT 0
#define TYPE_FLOAT 1

struct HashNode* symboltable[HASH_NUMBER+1];

struct StructName* structnametable;

typedef enum {BASIC, ARRAY, STRUCT, FUNC, ERROR} Kind;

typedef struct TypeInfo
{
    Kind kind;
    union
    {
        int basic; //BASIC
        struct
        {
            struct TypeInfo *element;
            int size;
        } array; //ARRAY
        struct FieldList *structure; //STRUCT
        struct Function *function; //FUNCTION
        int errortype; //ERROR
    } info;
} TypeInfo;

typedef struct FieldList
{
    char name[33];
    int linenumber;
    struct TypeInfo *typeinfo;
    struct FieldList *next;
} FieldList;

typedef struct Function
{
	int paranum;
	struct ParameterList *paralist;
	struct TypeInfo *functype;
} Function;

typedef struct ParameterList
{
    char name[33];
    int linenumber;
    struct TypeInfo *typeinfo;
    struct ParameterList *next;
} ParameterList;

typedef struct HashNode
{
    char name[33];
    struct TypeInfo *typeinfo;
    struct HashNode *next;
} HashNode;

typedef struct StructName
{
    char name[33];
    struct StructName *next;
} StructName;


//symboltable function
void initsymboltable();
int hash_func(char *name);
HashNode* findsymbol(char *name, Kind kind);
int checksymbol(char *name, int isfunc);
void insertsymbol(HashNode *node);
void printnodeinfo(HashNode *node);

//supplement tool function
void printTypeInfo(TypeInfo *type);
void printStruct(FieldList *field);
void printFunc(Function *func);
void printParameterList(ParameterList *param);
void copyTypeInfo(TypeInfo *type, TypeInfo *copytype); //type <-- copytype
void copyStruct(FieldList *list, FieldList *copylist); //list <-- copylist
void copyFunc(Function *func, Function *copyfunc); //func <-- copyfunc
void copyParameterList(ParameterList *param, ParameterList *copyparam); //param <-- copyparam
int isEqualType(TypeInfo *a, TypeInfo *b);
int isEqualStruct(FieldList *a, FieldList *b);
int isEqualFunc(Function *a, Function *b);

//processing syntax function
void semantic_analysis(TreeNode *root);
void extdeflist(TreeNode *p);
void extdef(TreeNode *p);
TypeInfo* specifier(TreeNode *p);
TypeInfo* structspecifier(TreeNode *p);
void extdeclist(TreeNode *p, TypeInfo *type);
void fundec(TreeNode *p, TypeInfo *type);
void structdeflist(TreeNode *p, FieldList *structinfo);
FieldList* structdef(TreeNode *p);
FieldList* structdeclist(TreeNode *p, TypeInfo *type);
FieldList* structdec(TreeNode *p, TypeInfo *type);
FieldList* vardec(TreeNode *p, TypeInfo *type);
ParameterList* varlist(TreeNode *p);
ParameterList* paramdec(TreeNode *p);
void compst(TreeNode *p, TypeInfo *type);
void stmtlist(TreeNode *p, TypeInfo *type);
void stmt(TreeNode *p, TypeInfo *type);
void funcdeflist(TreeNode *p);
void funcdef(TreeNode *p);
void funcdeclist(TreeNode *p,TypeInfo *type);
void funcdec(TreeNode *p,TypeInfo *type);
TypeInfo* Exp(TreeNode *p);
TypeInfo* expid(TreeNode *p);
TypeInfo* expfloat(TreeNode *p);
TypeInfo* expint(TreeNode *p);
TypeInfo* minusexp(TreeNode *p);
TypeInfo* notexp(TreeNode *p);
TypeInfo* callfunc(TreeNode *p);
TypeInfo* expassignop(TreeNode *p);
TypeInfo* expandor(TreeNode *p);
TypeInfo* callstruct(TreeNode *p);
TypeInfo* expcalculate(TreeNode *p);
TypeInfo* exprelop(TreeNode *p);
TypeInfo* callarray(TreeNode *p);
int args(TreeNode *p, ParameterList *param);
#endif






// TypeInfo *type = (TypeInfo*)malloc(sizeof(TypeInfo));
// FieldList *field = (FieldList*)malloc(sizeof(FieldList));
// HashNode *node = (HashNode*)malloc(sizeof(HashNode));
// ParameterList *paralist = (ParameterList*)malloc(sizeof(ParameterList));
// Function *func = (Function*)malloc(sizeof(Function));
