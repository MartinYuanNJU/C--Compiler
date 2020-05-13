#ifndef _INTERCODE_H_
#define _INTERCODE_H_

#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

typedef enum {LABEL_IC, FUNCTION_IC, ASSIGN, PLUS, SUB, MUL, DIV, GETADDR, RIGHTSTAR, LEFTSTAR, 
              GOTO, RELOPGOTO, RETURN, DEC, ARG, CALL, PARAM, READ, WRITE} InterCodeKind;

typedef enum {TEMP_VARIABLE, VARIABLE, CONSTANT, TEMP_ADDRESS, ADDRESS, STAR, 
              LABEL_OP, FUNCTION_OP, VARIABLE_CONSTANT, DEFAULT} OperandKind;

typedef struct Operand
{
    OperandKind kind;
    struct {
        int constant_value;
        char contents[33];
    } opinfo;

} Operand;

typedef struct InterCode
{
    InterCodeKind kind;
    union {
        struct {
            struct Operand *op;
        } singleop;
        struct {
            struct Operand *op1; //left
            struct Operand *op2; //right
        } doubleop; // op1 = op2
        struct {
            struct Operand *op;
            struct Operand *op1;
            struct Operand *op2;
        } tripleop; // op = op1 + op2
        struct {
            struct Operand *x;
            struct Operand *y;
            struct Operand *z;
            char relop[33];
        } relopgoto; // if x relop y goto z
        struct {
            struct Operand *op;
            int size;
        } dec;
    } codeinfo;

    struct InterCode *previous;
    struct InterCode *next;

} InterCode;

typedef struct structParameterList
{
    char structname[33];
    struct structParameterList *next;
} structParameterList;

typedef struct DuplicateLabel
{
    char labelname[33];
    struct DuplicateLabel *next;
} DuplicateLabel;

typedef struct LabelNode
{
    char labelname[33];
    struct LabelNode *next;
} LabelNode;

typedef struct VCList
{
    int vc_value;
    char vc_contents[33];
    int valid;
    struct VCList *next;
} VCList;

typedef struct VCvalue
{
    int value;
    int valid;
} VCvalue;

typedef struct Args
{
	Operand *one_arg;
	struct Args *next;
} Args;

struct InterCode *listhead;
struct InterCode *listtail;

struct structParameterList *paralisthead;

struct DuplicateLabel *duplabelhead;

struct LabelNode *labeltable[HASH_NUMBER+1];

struct VCList *vclisthead;

int label_no;
int tempvar_no;

//supplement tool function
void initialize();
void insertintercode(InterCode *intercode);
Operand* newOperand(OperandKind kind);
Operand* copyLabel(Operand *label);
Operand* copyOperand(Operand *op);
int calculatesize(TypeInfo *type);
void insertparalist(char name[33]);
int structisparameter(char name[33]);
void clearparalist();
void printOperand(Operand *op, FILE *fp);
void printIntercode(InterCode *head, FILE *fp);
void deleteintercode(InterCode *intercode);
void insertduplablelist(char name[33]);
int labelisduplicate(char name[33]);
void clearduplabellist();
void insertlabel(char name[33]);
int checklabel(char name[33]);
void insertvc(char name[33], int value, int valid);
void deletevc(char name[33]);
int variableisvc(char name[33]);
VCvalue* getvcvalue(char name[33]);

//generating intercode function
void generate_intercode(TreeNode *root, FILE *fp);
void extdeflist_intercode(TreeNode *p);
void extdef_intercode(TreeNode *p);
void fundec_intercode(TreeNode *p);
void compst_intercode(TreeNode *p);
void varlist_intercode(TreeNode *p);
void paramdec_intercode(TreeNode *p);
void funcvardec_intercode(TreeNode *p);
void funcdeflist_intercode(TreeNode *p);
void stmtlist_intercode(TreeNode *p);
void funcdef_intercode(TreeNode *p);
void funcdeclist_intercode(TreeNode *p);
void funcdec_intercode(TreeNode *p);
void vardec_intercode(TreeNode *p);
void exp_intercode(TreeNode *p, Operand *op);
void stmt_intercode(TreeNode *p);
void cond_intercode(TreeNode *p, Operand *label_true, Operand *label_false);
void expid_intercode(TreeNode *p, Operand *op);
void expint_intercode(TreeNode *p, Operand *op);
void minusexp_intercode(TreeNode *p, Operand *op);
void boolexp_intercode(TreeNode *p, Operand *op);
void callfunc_intercode(TreeNode *p, Operand *op);
Args* arg_intercode(TreeNode *p);
void expassignop_intercode(TreeNode *p, Operand *op);
void callstruct_intercode(TreeNode *p, Operand *op);
void expcalculate_intercode(TreeNode *p, Operand *op);
void callarray_intercode(TreeNode *p, Operand *op);
void optimize_intercode();
void delete_duplicate_label();
void delete_duplicate_goto();
void delete_duplicate_if();
void delete_useless_label();


#endif



// InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
// Operand *operand = (Operand*)malloc(sizeof(Operand));
// structParameterList *stparlist = (structParameterList*)malloc(sizeof(structParameterList));
// VCList *vcnode = (VCList*)malloc(sizeof(VCList));
// VCvalue *vcvalue = (VCvalue*)malloc(sizeof(VCvalue));