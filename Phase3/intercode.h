#ifndef _INTERCODE_H_
#define _INTERCODE_H_

#include <stdio.h>
#include "semantic.h"

typedef enum {LABEL, FUNCTION_IC, ASSIGN, PLUS, SUB, MUL, DIV, GETADDR, RIGHTSTAR, LEFTSTAR, 
              GOTO, RELOPGOTO, RETURN, DEC, ARG, CALL, PARAM, READ, WRITE} InterCodeKind;

typedef enum {TEMP_VARIABLE, VARIABLE, CONSTANT, TEMP_ADDRESS, ADDRESS, LABEL, FUNCTION_OP} OperandKind;

typedef struct Operand
{
    OperandKind kind;
    union {
        int tmpvar_no;
        int label_no;
        char contents[33];
        struct Operand *addr;
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
            char relop[10];
        } relopgoto; // if x relop y goto z
        struct {
            struct Operand *op;
            int size;
        } dec;
    } codeinfo;

    struct InterCode *previous;
    struct InterCode *next;

} InterCode;

struct InterCode *listhead;
struct InterCode *listtail;

int label_no;
int tempvar_no;

//supplement tool function
void initialize();
void insertintercode(InterCode *intercode);

//generating intercode function
void generate_intercode(TreeNode *root);
void extdeflist_intercode(TreeNode *p);
void extdef_intercode(TreeNode *p);
void fundec_intercode(TreeNode *p);
void compst_intercode(TreeNode *p);

#endif



// InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
// Operand *operand = (Operand*)malloc(sizeof(Operand));
