#include "objectcode.h"

int argnum;

//supplement tool function
void printdata(FILE *fp)
{
    fprintf(fp, ".data\n");
    fprintf(fp, "_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(fp, "_ret: .asciiz \"\\n\"\n");
    fprintf(fp, ".globl main\n");
    fprintf(fp, ".text\n");
    fprintf(fp, "read:\n");
    fprintf(fp, "li $v0, 4\n");
    fprintf(fp, "la $a0, _prompt\n");
    fprintf(fp, "syscall\n");
    fprintf(fp, "li $v0, 5\n");
    fprintf(fp, "syscall\n");
    fprintf(fp, "jr $ra\n");
    fprintf(fp, "\n");
    fprintf(fp, "write:\n");
    fprintf(fp, "li $v0, 1\n");
    fprintf(fp, "syscall\n");
    fprintf(fp, "li $v0, 4\n");
    fprintf(fp, "la $a0, _ret\n");
    fprintf(fp, "syscall\n");
    fprintf(fp, "move $v0, $0\n");
    fprintf(fp, "jr $ra\n\n");
}

void initialize_register()
{
    strcpy(regs[0].register_name, "$0");
    strcpy(regs[1].register_name, "$at");
    strcpy(regs[2].register_name, "$v0");
    strcpy(regs[3].register_name, "$v1");
    strcpy(regs[4].register_name, "$a0");
    strcpy(regs[5].register_name, "$a1");
    strcpy(regs[6].register_name, "$a2");
    strcpy(regs[7].register_name, "$a3");
    strcpy(regs[8].register_name, "$t0");
    strcpy(regs[9].register_name, "$t1");
    strcpy(regs[10].register_name, "$t2");
    strcpy(regs[11].register_name, "$t3");
    strcpy(regs[12].register_name, "$t4");
    strcpy(regs[13].register_name, "$t5");
    strcpy(regs[14].register_name, "$t6");
    strcpy(regs[15].register_name, "$t7");
    strcpy(regs[16].register_name, "$s0");
    strcpy(regs[17].register_name, "$s1");
    strcpy(regs[18].register_name, "$s2");
    strcpy(regs[19].register_name, "$s3");
    strcpy(regs[20].register_name, "$s4");
    strcpy(regs[21].register_name, "$s5");
    strcpy(regs[22].register_name, "$s6");
    strcpy(regs[23].register_name, "$s7");
    strcpy(regs[24].register_name, "$t8");
    strcpy(regs[25].register_name, "$t9");
    strcpy(regs[26].register_name, "$k0");
    strcpy(regs[27].register_name, "$k1");
    strcpy(regs[28].register_name, "$gp");
    strcpy(regs[29].register_name, "$sp");
    strcpy(regs[30].register_name, "$fp");
    strcpy(regs[31].register_name, "$ra");
    for(int i = 0; i < 32; i++)
    {
        regs[i].register_id = i;
        regs[i].occupied = 0;
        regs[i].vardescripter = NULL;
    }
}

int assgin_register()
{
    for(int i=8; i<=15; i++)
    {
        if(regs[i].occupied == 0)
        {
            regs[i].occupied = 1;
            return i;
        }
    }
    for(int i=24; i<=25; i++)
    {
        if(regs[i].occupied == 0)
        {
            regs[i].occupied = 1;
            return i;
        }
    }
    for(int i=16; i<=23; i++)
    {
        if(regs[i].occupied == 0)
        {
            regs[i].occupied = 1;
            return i;
        }
    }
    return 0;
}

void free_register(int reg_id)
{
    regs[reg_id].occupied = 0;
    if(regs[reg_id].vardescripter != NULL)
    {
        free(regs[reg_id].vardescripter);
        regs[reg_id].vardescripter = NULL;
    }
}

void read_from_memory(int reg_id, Operand *operand, FILE *fp)
{
    if(operand->kind == CONSTANT || operand->kind == VARIABLE_CONSTANT)
    {
        VariableDescripter *vardescripter = (VariableDescripter*)malloc(sizeof(VariableDescripter)); 
        vardescripter->operand = copyOperand(operand);
        vardescripter->register_id = reg_id;
        vardescripter->offset = 0;
        vardescripter->next = NULL;
        regs[reg_id].vardescripter = vardescripter;
        fprintf(fp, "li %s, %d\n",regs[reg_id].register_name, operand->opinfo.constant_value);
    }
    else if(operand->kind == TEMP_ADDRESS || operand->kind == ADDRESS)
    {
        VariableDescripter *vardescripter = getvardescripter(operand);
        vardescripter->register_id = reg_id;
        regs[reg_id].vardescripter = copyVarDes(vardescripter);
        fprintf(fp, "addi %s, $fp, %d\n",regs[reg_id].register_name, vardescripter->offset);
    }
    else if(operand->kind == STAR)
    {
        VariableDescripter *vardescripter = getvardescripter(operand);
        vardescripter->register_id = reg_id;
        regs[reg_id].vardescripter = copyVarDes(vardescripter);
        fprintf(fp, "lw %s, %d($fp)\n", regs[reg_id].register_name, vardescripter->offset);
        fprintf(fp, "lw %s, 0(%s)\n", regs[reg_id].register_name, regs[reg_id].register_name);
    }
    else
    {
        VariableDescripter *vardescripter = getvardescripter(operand);
        vardescripter->register_id = reg_id;
        regs[reg_id].vardescripter = copyVarDes(vardescripter);
        fprintf(fp, "lw %s, %d($fp)\n", regs[reg_id].register_name, vardescripter->offset);
    }
}

void insert_vardescripter(VariableDescripter *vardescripter)
{
    vardescripter->next = vardeshead;
    vardeshead = vardescripter;
}

void clear_vardescripter(VariableDescripter *head)
{
    while(head != NULL)
    {
        VariableDescripter *p = head;
        head = head->next;
        // if(p->operand != NULL)
        // {
        //     free(p->operand);
        //     p->operand = NULL;
        // }
        free(p);
    }
}

VariableDescripter* copyVarDes(VariableDescripter *vd)
{
    VariableDescripter *copyvd = (VariableDescripter*)malloc(sizeof(VariableDescripter));
    copyvd->operand = copyOperand(vd->operand);
    copyvd->register_id = vd->register_id;
    copyvd->offset = vd->offset;
    copyvd->next = NULL;
    return copyvd;
}

VariableDescripter* getvardescripter(Operand *operand)
{
    if(operand->kind == CONSTANT || operand->kind == VARIABLE_CONSTANT)
        return NULL;
    for(VariableDescripter *p=vardeshead; p!=NULL; p=p->next)
    {
        if(p->operand->kind != CONSTANT && p->operand->kind != VARIABLE_CONSTANT)
        {
            if(strcmp(operand->opinfo.contents, p->operand->opinfo.contents) == 0)
                return p;
        }
    }
    return NULL;
}

//generating objectcode
void generate_objectcode(FILE *fp)
{
    if(errorsum != 0)
        return;

    printdata(fp);
    initialize_register();

    vardeshead = NULL;

    argnum = 0;

    //generate_intercode
    for(InterCode *p=listhead; p!=NULL; p=p->next)
    {
        if(p->kind == LABEL_IC)
            label_objectcode(p, fp);
        else if(p->kind == FUNCTION_IC)
            function_objectcode(p, fp);
        else if(p->kind == ASSIGN)
            assgin_objectcode(p, fp);
        else if(p->kind == PLUS)
            plus_objectcode(p, fp);
        else if(p->kind == SUB)
            sub_objectcode(p, fp);
        else if(p->kind == MUL)
            mul_objectcode(p, fp);
        else if(p->kind == DIV)
            div_objectcode(p, fp);
        else if(p->kind == GOTO)
            goto_objectcode(p, fp);
        else if(p->kind == RELOPGOTO)
            relopgoto_objectcode(p, fp);
        else if(p->kind == RETURN)
            return_objectcode(p, fp);
        else if(p->kind == DEC)
        {

        }
        else if(p->kind == ARG)
            arg_objectcode(p, fp);
        else if(p->kind == CALL)
            call_objectcode(p, fp);
        else if(p->kind == PARAM)
        {

        }
        else if(p->kind == READ)
        {

        }
        else if(p->kind == WRITE)
        {

        }
    }
}

void label_objectcode(InterCode *p, FILE *fp)
{
    fprintf(fp, "%s:\n", p->codeinfo.singleop.op->opinfo.contents);
}

void function_objectcode(InterCode *p, FILE *fp)
{

}

void assgin_objectcode(InterCode *p, FILE *fp)
{
    if(p->codeinfo.doubleop.op1->kind == STAR)
    {
        int rightreg = assgin_register();
        read_from_memory(rightreg, p->codeinfo.doubleop.op2, fp);
        int leftreg = assgin_register();
        VariableDescripter *vd = getvardescripter(p->codeinfo.doubleop.op1);
        fprintf(fp, "lw %s, %d($fp)\n", regs[leftreg].register_name, vd->offset);
        fprintf(fp, "sw %s, 0(%s)\n", regs[rightreg].register_name, regs[leftreg].register_name);
        free_register(leftreg);
        free_register(rightreg);
    }
    else if(p->codeinfo.doubleop.op1->kind == TEMP_VARIABLE || p->codeinfo.doubleop.op1->kind == VARIABLE)
    {
        int rightreg = assgin_register();
        read_from_memory(rightreg, p->codeinfo.doubleop.op2, fp);
        int leftreg = assgin_register();
        read_from_memory(leftreg, p->codeinfo.doubleop.op1, fp);
        fprintf(fp, "move %s, %s\n", regs[leftreg].register_name, regs[rightreg].register_name);
        fprintf(fp, "sw %s, %d($fp)\n", regs[leftreg].register_name, regs[leftreg].vardescripter->offset);
        free_register(leftreg);
        free_register(rightreg);
    }
    else
    {
        printf("unhandled situation at assgin_objectcode, left operand type: %d\n", p->codeinfo.doubleop.op1->kind);
    }
}

void plus_objectcode(InterCode *p, FILE *fp)
{

}

void sub_objectcode(InterCode *p, FILE *fp)
{

}

void mul_objectcode(InterCode *p, FILE *fp)
{

}

void div_objectcode(InterCode *p, FILE *fp)
{

}

void goto_objectcode(InterCode *p, FILE *fp)
{
    fprintf(fp, "j %s\n", p->codeinfo.singleop.op->opinfo.contents);
}

void relopgoto_objectcode(InterCode *p, FILE *fp)
{
    int xreg = assgin_register();
    int yreg = assgin_register();
    read_from_memory(xreg, p->codeinfo.relopgoto.x, fp);
    read_from_memory(yreg, p->codeinfo.relopgoto.y, fp);
    char relop[33];
    strcpy(relop, p->codeinfo.relopgoto.relop);
    if(strcmp(relop, "==") == 0)
    {
        fprintf(fp, "beq %s, %s, %s\n", regs[xreg].register_name, regs[yreg].register_name, p->codeinfo.relopgoto.z->opinfo.contents);
    }
    else if(strcmp(relop, "!=") == 0)
    {
        fprintf(fp, "bne %s, %s, %s\n", regs[xreg].register_name, regs[yreg].register_name, p->codeinfo.relopgoto.z->opinfo.contents);
    }
    else if(strcmp(relop, ">") == 0)
    {
        fprintf(fp, "bgt %s, %s, %s\n", regs[xreg].register_name, regs[yreg].register_name, p->codeinfo.relopgoto.z->opinfo.contents);
    }
    else if(strcmp(relop, "<") == 0)
    {
        fprintf(fp, "blt %s, %s, %s\n", regs[xreg].register_name, regs[yreg].register_name, p->codeinfo.relopgoto.z->opinfo.contents);
    }
    else if(strcmp(relop, ">=") == 0)
    {
        fprintf(fp, "bge %s, %s, %s\n", regs[xreg].register_name, regs[yreg].register_name, p->codeinfo.relopgoto.z->opinfo.contents);
    }
    else if(strcmp(relop, "<=") == 0)
    {
        fprintf(fp, "ble %s, %s, %s\n", regs[xreg].register_name, regs[yreg].register_name, p->codeinfo.relopgoto.z->opinfo.contents);
    }
    free_register(xreg);
    free_register(yreg);
}

void return_objectcode(InterCode *p, FILE *fp)
{

}

void arg_objectcode(InterCode *p, FILE *fp)
{

}

void call_objectcode(InterCode *p, FILE *fp)
{

}