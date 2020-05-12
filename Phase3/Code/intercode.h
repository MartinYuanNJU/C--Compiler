#ifndef _INTERCODE_H_
#define _INTERCODE_H_

#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

typedef enum {LABEL_IC, FUNCTION_IC, ASSIGN, PLUS, SUB, MUL, DIV, GETADDR, RIGHTSTAR, LEFTSTAR, 
              GOTO, RELOPGOTO, RETURN, DEC, ARG, CALL, PARAM, READ, WRITE} InterCodeKind;

typedef enum {TEMP_VARIABLE, VARIABLE, CONSTANT, TEMP_ADDRESS, ADDRESS, STAR, LABEL_OP, FUNCTION_OP, DEFAULT} OperandKind;

typedef struct Operand
{
    OperandKind kind;
    union {
        int constant_value;
        char contents[33];
        //struct Operand *addr;
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

typedef struct Args
{
	Operand *one_arg;
	struct Args *next;
} Args;

struct InterCode *listhead;
struct InterCode *listtail;

struct structParameterList *paralisthead;

struct DuplicateLabel *duplabelhead;

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
void printoperand(Operand *op);
void printIntercode(InterCode *head, FILE *fp);
void deleteintercode(InterCode *intercode);
void insertduplablelist(char name[33]);
int labelisduplicate(char name[33]);
void clearduplabellist();
void delete_duplicate_goto();
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

#endif



// InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
// Operand *operand = (Operand*)malloc(sizeof(Operand));
// structParameterList *stparlist = (structParameterList*)malloc(sizeof(structParameterList));
