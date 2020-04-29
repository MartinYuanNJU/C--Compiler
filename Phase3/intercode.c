#include "intercode.h"

extern int errorsum;

void initialize()
{
    TypeInfo *readtype = (TypeInfo*)malloc(sizeof(TypeInfo));
    readtype->kind = FUNC;
    Function *funcread = (Function*)malloc(sizeof(Function));
    funcread->functype = (TypeInfo*)malloc(sizeof(TypeInfo));
    funcread->functype->kind = BASIC;
    funcread->functype->info.basic = TYPE_INT;
    funcread->paranum = 0;
    funcread->paralist = NULL;
    readtype->info.function = funcread;

    TypeInfo *writetype = (TypeInfo*)malloc(sizeof(TypeInfo));
    writetype->kind = FUNC;
    Function *funcwrite = (Function*)malloc(sizeof(Function));
    funcwrite->functype = (TypeInfo*)malloc(sizeof(TypeInfo));
    funcwrite->functype->kind = BASIC;
    funcwrite->functype->info.basic = TYPE_INT;
    funcwrite->paranum = 1;
    ParameterList *paralist = (ParameterList*)malloc(sizeof(ParameterList));
    TypeInfo *type = (TypeInfo*)malloc(sizeof(TypeInfo));
    type->kind = BASIC;
    type->info.basic = TYPE_INT;
    paralist->typeinfo = type;
    paralist->next = NULL;
    funcwrite->paralist = paralist;
    writetype->info.function = funcwrite;

    HashNode *readnode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(readnode->name, "read");
    readnode->typeinfo = readtype;
    readnode->next = NULL;
    insertsymbol(readnode);

    HashNode *writenode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(writenode->name, "write");
    writenode->typeinfo = writetype;
    writenode->next = NULL;
    insertsymbol(writenode);

    listhead = NULL;
    listtail = NULL;

    label_no = 1;
    tempvar_no = 1;
}

void insertintercode(InterCode *intercode)
{
    if(listhead == NULL)
    {
        listhead = intercode;
        listtail = intercode;
        listhead->previous = NULL;
        listhead->next = NULL;
    }
    else
    {
        listtail->next = intercode;
        intercode->previous = listtail;
        intercode->next = NULL;
        listtail = intercode;
    }
}

//generating intercode
void generate_intercode(TreeNode *root)
{
    if(errorsum != 0)
        return;
    if(root == NULL)
        return;
    initialize();
    extdeflist_intercode(root->children[0]);
}

void extdeflist_intercode(TreeNode *p)
{
    if(p == NULL)
        return;
    extdef_intercode(p->children[0]);
    extdeflist_intercode(p->children[1]);
}

void extdef_intercode(TreeNode *p)
{
    if(strcmp(p->children[1]->contents, "FunDec")==0)
    {
        fundec_intercode(p->children[1]);
        compst_intercode(p->children[2]);
    }
}

void fundec_intercode(TreeNode *p)
{
    //intercode: FUNCTION x
    InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
    Operand *operand = (Operand*)malloc(sizeof(Operand));
    // wxy writes operand->kind = VARIABLE;
    operand->kind = FUNCTION_OP;
    strcpy(operand->opinfo.contents, p->children[0]->contents);
    intercode->kind = FUNCTION_IC;
    intercode->codeinfo.singleop.op = operand;
    insertintercode(intercode);
    if(p->childrennum == 4)
        varlist_intercode(p->children[2]);
}