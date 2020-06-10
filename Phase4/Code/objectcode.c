#include "objectcode.h"
#define OFFSET_CORRECT -8

int argnum;

int variable_offset;

void printOperand_commandline(Operand *op)
{
    if(op->kind == CONSTANT || op->kind == VARIABLE_CONSTANT)
        printf("#%d",op->opinfo.constant_value);
    else if(op->kind == TEMP_ADDRESS || op->kind == ADDRESS)
        printf("&%s",op->opinfo.contents);
    else if(op->kind == STAR)
        printf("*%s",op->opinfo.contents);
    else
        printf("%s",op->opinfo.contents);
}

void printOperand_commandlineenter(Operand *op)
{
    if(op->kind == CONSTANT || op->kind == VARIABLE_CONSTANT)
        printf("#%d",op->opinfo.constant_value);
    else if(op->kind == TEMP_ADDRESS || op->kind == ADDRESS)
        printf("&%s",op->opinfo.contents);
    else if(op->kind == STAR)
        printf("*%s",op->opinfo.contents);
    else
        printf("%s",op->opinfo.contents);
    printf("\n");
}

void printIntercode_commandline(InterCode *p)
{
        if(p->kind == LABEL_IC)
            printf("LABEL %s :", p->codeinfo.singleop.op->opinfo.contents);
        else if(p->kind == FUNCTION_IC)
            printf("FUNCTION %s :", p->codeinfo.singleop.op->opinfo.contents);
        else if(p->kind == ASSIGN)
        {
            printOperand_commandline(p->codeinfo.doubleop.op1);
            printf(" := ");
            printOperand_commandline(p->codeinfo.doubleop.op2);
        }
        else if(p->kind == PLUS)
        {
            printOperand_commandline(p->codeinfo.tripleop.op);
            printf(" := ");
            printOperand_commandline(p->codeinfo.tripleop.op1);
            printf(" + ");
            printOperand_commandline(p->codeinfo.tripleop.op2);
        }
        else if(p->kind == SUB)
        {
            printOperand_commandline(p->codeinfo.tripleop.op);
            printf(" := ");
            printOperand_commandline(p->codeinfo.tripleop.op1);
            printf(" - ");
            printOperand_commandline(p->codeinfo.tripleop.op2);
        }
        else if(p->kind == MUL)
        {
            printOperand_commandline(p->codeinfo.tripleop.op);
            printf(" := ");
            printOperand_commandline(p->codeinfo.tripleop.op1);
            printf(" * ");
            printOperand_commandline(p->codeinfo.tripleop.op2);
        }
        else if(p->kind == DIV)
        {
            printOperand_commandline(p->codeinfo.tripleop.op);
            printf(" := ");
            printOperand_commandline(p->codeinfo.tripleop.op1);
            printf(" / ");
            printOperand_commandline(p->codeinfo.tripleop.op2);
        }
        else if(p->kind == GOTO)
        {
            printf("GOTO ");
            printOperand_commandline(p->codeinfo.singleop.op);
        }
        else if(p->kind == RELOPGOTO)
        {
            printf("IF ");
            printOperand_commandline(p->codeinfo.relopgoto.x);
            printf(" %s ",p->codeinfo.relopgoto.relop);
            printOperand_commandline(p->codeinfo.relopgoto.y);
            printf(" GOTO ");
            printOperand_commandline(p->codeinfo.relopgoto.z);
        }
        else if(p->kind == RETURN)
        {
            printf("RETURN ");
            printOperand_commandline(p->codeinfo.singleop.op);
        }
        else if(p->kind == DEC)
        {
            printf("DEC ");
            printOperand_commandline(p->codeinfo.dec.op);
            printf(" %d", p->codeinfo.dec.size);
        }
        else if(p->kind == ARG)
        {
            printf("ARG ");
            printOperand_commandline(p->codeinfo.singleop.op);
        }
        else if(p->kind == CALL)
        {
            printOperand_commandline(p->codeinfo.doubleop.op1);
            printf(" := CALL ");
            printOperand_commandline(p->codeinfo.doubleop.op2);
        }
        else if(p->kind == PARAM)
        {
            printf("PARAM ");
            printOperand_commandline(p->codeinfo.singleop.op);
        }
        else if(p->kind == READ)
        {
            printf("READ ");
            printOperand_commandline(p->codeinfo.singleop.op);
        }
        else if(p->kind == WRITE)
        {
            printf("WRITE ");
            printOperand_commandline(p->codeinfo.singleop.op);
        }
        printf("\n");
}

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
    fprintf(fp, "jr $ra\n");
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

void freeall_register()
{
    for(int i=8; i<=15; i++)
    {
        free_register(i);
    }
    for(int i=24; i<=25; i++)
    {
        free_register(i);
    }
    for(int i=16; i<=23; i++)
    {
        free_register(i);
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

void insert_operand(Operand *operand)
{
    if(operand->kind == CONSTANT || operand->kind == VARIABLE_CONSTANT)
        return;
    VariableDescripter *vardescripter = getvardescripter(operand);
    if(vardescripter != NULL)
        return;
    VariableDescripter *vd = (VariableDescripter*)malloc(sizeof(VariableDescripter));
    vd->operand = copyOperand(operand);
    variable_offset -= 4;
    vd->offset = variable_offset + OFFSET_CORRECT;
    insert_vardescripter(vd);
}

void clear_vardescripter()
{
    while(vardeshead != NULL)
    {
        VariableDescripter *p = vardeshead;
        vardeshead = vardeshead->next;
        if(p->operand != NULL)
        {
            free(p->operand);
            p->operand = NULL;
        }
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

    variable_offset = 0;

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
        else if(p->kind == ARG)
            arg_objectcode(p, fp);
        else if(p->kind == CALL)
            call_objectcode(p, fp);
        else if(p->kind == READ)
	        read_objectcode(p, fp);
        else if(p->kind == WRITE)
	        write_objectcode(p, fp);
    }
}

void label_objectcode(InterCode *p, FILE *fp)
{
    fprintf(fp, "%s:\n", p->codeinfo.singleop.op->opinfo.contents);
}

void function_objectcode(InterCode *p, FILE *fp)
{
    char funcname[50];
    if(strcmp(p->codeinfo.singleop.op->opinfo.contents, "main") == 0)
    {
        strcpy(funcname, "main");
    }
    else
    {
        strcpy(funcname, "func_");
        strcat(funcname, p->codeinfo.singleop.op->opinfo.contents);
    }
    fprintf(fp, "\n%s:\n", funcname);

    clear_vardescripter();

    //save return address
    fprintf(fp, "addi $sp, $sp, -4\n");
    fprintf(fp, "sw $ra, 0($sp)\n");
    //save this function's fp
    fprintf(fp, "addi $sp, $sp, -4\n");
    fprintf(fp, "sw $fp, 0($sp)\n");
    //make fp points to new stack frame
    fprintf(fp, "move $fp, $sp\n");
    fprintf(fp, "addi $fp, $fp, 8\n");

    variable_offset = 0;
    int paraoffset = 0;
    InterCode *q = p->next;
    for(; q != NULL && q->kind == PARAM; q = q->next)
    {
        VariableDescripter *vd = (VariableDescripter*)malloc(sizeof(VariableDescripter));
        vd->operand = copyOperand(q->codeinfo.singleop.op);
        vd->offset = paraoffset;
        insert_vardescripter(vd);
        paraoffset += 4;
    }
    for(; q != NULL && q->kind != FUNCTION_IC; q = q->next)
    {
        if(q->kind == ASSIGN)
        {
            insert_operand(q->codeinfo.doubleop.op1);
            insert_operand(q->codeinfo.doubleop.op2);
        }
        else if(q->kind == PLUS)
        {
	        insert_operand(q->codeinfo.tripleop.op);
	        insert_operand(q->codeinfo.tripleop.op1);
            insert_operand(q->codeinfo.tripleop.op2);
        }
        else if(q->kind == SUB)
        {
	        insert_operand(q->codeinfo.tripleop.op);
	        insert_operand(q->codeinfo.tripleop.op1);
            insert_operand(q->codeinfo.tripleop.op2);
        }
        else if(q->kind == MUL)
        {
	        insert_operand(q->codeinfo.tripleop.op);
	        insert_operand(q->codeinfo.tripleop.op1);
            insert_operand(q->codeinfo.tripleop.op2);
        }
        else if(q->kind == DIV)
        {
	        insert_operand(q->codeinfo.tripleop.op);
	        insert_operand(q->codeinfo.tripleop.op1);
            insert_operand(q->codeinfo.tripleop.op2);
        }
        else if(q->kind == RELOPGOTO)
        {
	        insert_operand(q->codeinfo.relopgoto.x);
	        insert_operand(q->codeinfo.relopgoto.y);
        }
        else if(q->kind == RETURN)
        {
	        insert_operand(q->codeinfo.singleop.op);
        }
        else if(q->kind == DEC)
        {
            variable_offset -= q->codeinfo.dec.size;
            VariableDescripter *vd = (VariableDescripter*)malloc(sizeof(VariableDescripter));
            vd->operand = copyOperand(q->codeinfo.dec.op);
            vd->offset = variable_offset + OFFSET_CORRECT;
            insert_vardescripter(vd);
        }
        else if(q->kind == ARG)
        {
	        insert_operand(q->codeinfo.singleop.op);
        }
        else if(q->kind == CALL)
        {
            insert_operand(q->codeinfo.doubleop.op1);
        }
        else if(q->kind == READ)
        {
	        insert_operand(q->codeinfo.singleop.op);
        }
        else if(q->kind == WRITE)
        {
	        insert_operand(q->codeinfo.singleop.op);
        }
    }
    //assign stack space for these variables
    fprintf(fp, "addi $sp, $sp, %d\n", variable_offset);
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
		int rightreg1=assgin_register();
		read_from_memory(rightreg1, p->codeinfo.tripleop.op1, fp);
		int rightreg2=assgin_register();
		read_from_memory(rightreg2, p->codeinfo.tripleop.op2, fp);
		int leftreg = assgin_register();
        read_from_memory(leftreg, p->codeinfo.tripleop.op, fp);
		fprintf(fp, "add %s, %s, %s\n",regs[leftreg].register_name,regs[rightreg1].register_name,regs[rightreg2].register_name);
		fprintf(fp, "sw %s, %d($fp)\n", regs[leftreg].register_name, regs[leftreg].vardescripter->offset);
        free_register(leftreg);
        free_register(rightreg1);
		free_register(rightreg2);
}

void sub_objectcode(InterCode *p, FILE *fp)
{
		int rightreg1=assgin_register();
		read_from_memory(rightreg1, p->codeinfo.tripleop.op1, fp);
		int rightreg2=assgin_register();
		read_from_memory(rightreg2, p->codeinfo.tripleop.op2, fp);
		int leftreg = assgin_register();
        read_from_memory(leftreg, p->codeinfo.tripleop.op, fp);
		fprintf(fp, "sub %s, %s, %s\n",regs[leftreg].register_name,regs[rightreg1].register_name,regs[rightreg2].register_name);
		fprintf(fp, "sw %s, %d($fp)\n", regs[leftreg].register_name, regs[leftreg].vardescripter->offset);
        free_register(leftreg);
        free_register(rightreg1);
		free_register(rightreg2);
}

void mul_objectcode(InterCode *p, FILE *fp)
{
		int rightreg1=assgin_register();
		read_from_memory(rightreg1, p->codeinfo.tripleop.op1, fp);
		int rightreg2=assgin_register();
		read_from_memory(rightreg2, p->codeinfo.tripleop.op2, fp);
		int leftreg = assgin_register();
        read_from_memory(leftreg, p->codeinfo.tripleop.op, fp);
		fprintf(fp, "mul %s, %s, %s\n",regs[leftreg].register_name,regs[rightreg1].register_name,regs[rightreg2].register_name);
		fprintf(fp, "sw %s, %d($fp)\n", regs[leftreg].register_name, regs[leftreg].vardescripter->offset);
        free_register(leftreg);
        free_register(rightreg1);
		free_register(rightreg2);
}

void div_objectcode(InterCode *p, FILE *fp)
{
		int rightreg1=assgin_register();
		read_from_memory(rightreg1, p->codeinfo.tripleop.op1, fp);
		int rightreg2=assgin_register();
		read_from_memory(rightreg2, p->codeinfo.tripleop.op2, fp);
		int leftreg = assgin_register();
        read_from_memory(leftreg, p->codeinfo.tripleop.op, fp);
		fprintf(fp, "div %s, %s, %s\n",regs[leftreg].register_name,regs[rightreg1].register_name,regs[rightreg2].register_name);
		fprintf(fp, "sw %s, %d($fp)\n", regs[leftreg].register_name, regs[leftreg].vardescripter->offset);
        free_register(leftreg);
        free_register(rightreg1);
		free_register(rightreg2);
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
    //get return address
    fprintf(fp, "lw $ra, -4($fp)\n");
    //recover $sp value
    fprintf(fp, "move $sp, $fp\n");
    //get the reg of the return value (here has old $fp)
    int regid = assgin_register();
    read_from_memory(regid, p->codeinfo.singleop.op, fp);
    //recover $fp value;
    fprintf(fp, "lw $fp, -8($fp)\n");
    //get return value into $v0
    fprintf(fp, "move $v0, %s\n", regs[regid].register_name);
    //jump to return address
    fprintf(fp, "jr $ra\n");
    //free all register
    freeall_register();
}

void arg_objectcode(InterCode *p, FILE *fp)
{
    //develop a space in stack for the argument
    fprintf(fp, "addi $sp, $sp, -4\n");
    //then get the argument into a register
    int regid = assgin_register();
    read_from_memory(regid, p->codeinfo.singleop.op, fp);
    //then move the register's value into the stack
    fprintf(fp, "sw %s, 0($sp)\n", regs[regid].register_name);
    //then free this register
    free_register(regid);
    //then argument number increase one
    argnum++;
}

void call_objectcode(InterCode *p, FILE *fp)
{
    char funcname[50];
    if(strcmp(p->codeinfo.doubleop.op2->opinfo.contents, "main") == 0)
    {
        strcpy(funcname, "main");
    }
    else
    {
        strcpy(funcname, "func_");
        strcat(funcname, p->codeinfo.doubleop.op2->opinfo.contents);
    }
    fprintf(fp, "jal %s\n", funcname);
    int regid = assgin_register();
    read_from_memory(regid, p->codeinfo.doubleop.op1, fp);
    fprintf(fp, "move %s, $v0\n", regs[regid].register_name);
    fprintf(fp, "sw %s, %d($fp)\n", regs[regid].register_name, regs[regid].vardescripter->offset);
    free_register(regid);
    argnum *= 4;
    fprintf(fp, "addi $sp, $sp, %d\n", argnum);
    argnum = 0;
}

void read_objectcode(InterCode *p, FILE *fp)
{
	fprintf(fp, "addi $sp, $sp, -4\n");
	fprintf(fp, "sw $ra, 0($sp)\n");
	fprintf(fp, "jal read\n");
	fprintf(fp, "lw $ra, 0($sp)\n");
	fprintf(fp, "addi $sp, $sp, 4\n");
	int res = assgin_register();
    read_from_memory(res, p->codeinfo.singleop.op, fp);
	fprintf(fp, "move %s, $v0\n",regs[res].register_name);
	fprintf(fp, "sw %s, %d($fp)\n", regs[res].register_name, regs[res].vardescripter->offset);
	free_register(res);
}

void write_objectcode(InterCode *p, FILE *fp)
{
	int res = assgin_register();
    read_from_memory(res, p->codeinfo.singleop.op, fp);
	fprintf(fp, "move $a0, %s\n", regs[res].register_name);
	fprintf(fp, "addi $sp, $sp, -4\n");
	fprintf(fp, "sw $ra, 0($sp)\n");
	fprintf(fp, "jal write\n");
	fprintf(fp, "lw $ra, 0($sp)\n");
	fprintf(fp, "addi $sp, $sp, 4\n");
	free_register(res);
}
