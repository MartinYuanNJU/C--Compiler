#ifndef _OBJECTCODE_H_
#define _OBJECTCODE_H_

#include <stdio.h>
#include <stdlib.h>
#include "intercode.h"

extern int errorsum;

extern struct InterCode *listhead;

typedef struct VariableDescripter
{
    struct Operand *operand;
    int register_id;
    int offset;
    struct VariableDescripter *next;

} VariableDescripter;

typedef struct RegisterDescripter
{
    int register_id;
    char register_name[10];
    int occupied;
    struct VariableDescripter *vardescripter;

} RegisterDescripter;

RegisterDescripter regs[32];

struct VariableDescripter *vardeshead;

void printdata(FILE *fp);
void initialize_register();
int assgin_register();
void read_from_memory(int reg_id, Operand *operand, FILE *fp);
//void write_to_memory(int reg_id);
void free_register(int reg_id);
void freeall_register();
void insert_vardescripter(VariableDescripter *vardescripter);
void insert_operand(Operand *operand);
void clear_vardescripter(VariableDescripter *head);
VariableDescripter* getvardescripter(Operand *operand);
VariableDescripter* copyVarDes(VariableDescripter *vd);

void generate_objectcode(FILE *fp);
void label_objectcode(InterCode *p, FILE *fp);
void function_objectcode(InterCode *p, FILE *fp);
void assgin_objectcode(InterCode *p, FILE *fp);
void plus_objectcode(InterCode *p, FILE *fp);
void sub_objectcode(InterCode *p, FILE *fp);
void mul_objectcode(InterCode *p, FILE *fp);
void div_objectcode(InterCode *p, FILE *fp);
void goto_objectcode(InterCode *p, FILE *fp);
void relopgoto_objectcode(InterCode *p, FILE *fp);
void return_objectcode(InterCode *p, FILE *fp);
void arg_objectcode(InterCode *p, FILE *fp);
void call_objectcode(InterCode *p, FILE *fp);

#endif

// VariableDescripter *vardescripter = (VariableDescripter*)malloc(sizeof(VariableDescripter));