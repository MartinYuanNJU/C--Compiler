#include "intercode.h"

extern int errorsum;
int printnode_intercode = 0;

void initialize()
{
    listhead = NULL;
    listtail = NULL;

    paralisthead = NULL;

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

Operand* newOperand(OperandKind kind)
{
    Operand *operand = (Operand*)malloc(sizeof(Operand));
    if(kind == TEMP_VARIABLE)
    {
        char contents[33];
        strcpy(contents, "TEMPVAR");
        char number[33];
        sprintf(number, "%d", tempvar_no);
        strcat(contents, number);
        operand->kind = TEMP_VARIABLE;
        strcpy(operand->opinfo.contents, contents);
        tempvar_no++;
    }
    else if(kind == LABEL_OP)
    {
        char contents[33];
        strcpy(contents, "LABEL");
        char number[33];
        sprintf(number, "%d", label_no);
        strcat(contents, number);
        operand->kind = LABEL_OP;
        strcpy(operand->opinfo.contents, contents);
        label_no++;
    }
    else
        operand = NULL;
    return operand;
}

Operand* copyLabel(Operand *label)
{
    Operand *operand = (Operand*)malloc(sizeof(Operand));
    operand->kind = LABEL_OP;
    strcpy(operand->opinfo.contents, label->opinfo.contents);
    return operand;
}

Operand* copyOperand(Operand *op)
{
    Operand *operand = (Operand*)malloc(sizeof(Operand));
    operand->kind = op->kind;
    if(op->kind == CONSTANT)
        operand->opinfo.constant_value = op->opinfo.constant_value;
    else
        strcpy(operand->opinfo.contents, op->opinfo.contents);
    return operand; 
}

int calculatesize(TypeInfo *type)
{
    if(type->kind == BASIC)
        return 4;
    else if(type->kind == ARRAY)
        return type->info.array.size * calculatesize(type->info.array.element);
    else if(type->kind == STRUCT)
    {
        int size = 0;
        FieldList *list = type->info.structure;
        while(list != NULL)
        {
            size += calculatesize(list->typeinfo);
            list = list->next;
        }
        return size;
    }
    else
        return 0;
}

void insertparalist(char name[33])
{
    structParameterList *stparlist = (structParameterList*)malloc(sizeof(structParameterList));
    strcpy(stparlist->structname, name);
    stparlist->next = paralisthead;
    paralisthead = stparlist;
}

int structisparameter(char name[33])
{
    structParameterList *stparlist = paralisthead;
    while(stparlist != NULL)
    {
        if(strcmp(stparlist->structname, name)==0)
            return 1;
        stparlist = stparlist->next;
    }
    return 0;
}

void clearparalist()
{
    while(paralisthead != NULL)
    {
        structParameterList *stparlist = paralisthead;
        paralisthead = paralisthead->next;
        free(stparlist);
    }
}

void printOperand(Operand *op, FILE *fp)
{
    if(op->kind == CONSTANT)
        fprintf(fp, "#%d",op->opinfo.constant_value);
    else if(op->kind == TEMP_ADDRESS || op->kind == ADDRESS)
        fprintf(fp,"&%s",op->opinfo.contents);
    else if(op->kind == STAR)
        fprintf(fp, "*%s",op->opinfo.contents);
    else
        fprintf(fp, "%s",op->opinfo.contents);
}

void printoperand(Operand *op)
{
    if(op->kind == CONSTANT)
        printf("#%d",op->opinfo.constant_value);
    else if(op->kind == TEMP_ADDRESS || op->kind == ADDRESS)
        printf("&%s",op->opinfo.contents);
    else if(op->kind == STAR)
        printf("*%s",op->opinfo.contents);
    else
        printf("%s",op->opinfo.contents);
}

void printIntercode(InterCode *head, FILE *fp)
{
    for(InterCode *p=head; p!=NULL; p=p->next)
    {
        if(p->kind == LABEL_IC)
            fprintf(fp, "LABEL %s :", p->codeinfo.singleop.op->opinfo.contents);
        else if(p->kind == FUNCTION_IC)
            fprintf(fp, "FUNCTION %s :", p->codeinfo.singleop.op->opinfo.contents);
        else if(p->kind == ASSIGN)
        {
            printOperand(p->codeinfo.doubleop.op1, fp);
            fprintf(fp, " := ");
            printOperand(p->codeinfo.doubleop.op2, fp);
        }
        else if(p->kind == PLUS)
        {
            printOperand(p->codeinfo.tripleop.op, fp);
            fprintf(fp, " := ");
            printOperand(p->codeinfo.tripleop.op1, fp);
            fprintf(fp, " + ");
            printOperand(p->codeinfo.tripleop.op2, fp);
        }
        else if(p->kind == SUB)
        {
            printOperand(p->codeinfo.tripleop.op, fp);
            fprintf(fp, " := ");
            printOperand(p->codeinfo.tripleop.op1, fp);
            fprintf(fp, " - ");
            printOperand(p->codeinfo.tripleop.op2, fp);
        }
        else if(p->kind == MUL)
        {
            printOperand(p->codeinfo.tripleop.op, fp);
            fprintf(fp, " := ");
            printOperand(p->codeinfo.tripleop.op1, fp);
            fprintf(fp, " * ");
            printOperand(p->codeinfo.tripleop.op2, fp);
        }
        else if(p->kind == DIV)
        {
            printOperand(p->codeinfo.tripleop.op, fp);
            fprintf(fp, " := ");
            printOperand(p->codeinfo.tripleop.op1, fp);
            fprintf(fp, " / ");
            printOperand(p->codeinfo.tripleop.op2, fp);
        }
        else if(p->kind == GOTO)
        {
            fprintf(fp, "GOTO ");
            printOperand(p->codeinfo.singleop.op, fp);
        }
        else if(p->kind == RELOPGOTO)
        {
            fprintf(fp, "IF ");
            printOperand(p->codeinfo.relopgoto.x, fp);
            fprintf(fp, " %s ",p->codeinfo.relopgoto.relop);
            printOperand(p->codeinfo.relopgoto.y, fp);
            fprintf(fp, " GOTO ");
            printOperand(p->codeinfo.relopgoto.z, fp);
        }
        else if(p->kind == RETURN)
        {
            fprintf(fp, "RETURN ");
            printOperand(p->codeinfo.singleop.op, fp);
        }
        else if(p->kind == DEC)
        {
            fprintf(fp, "DEC ");
            printOperand(p->codeinfo.dec.op, fp);
            fprintf(fp, " %d", p->codeinfo.dec.size);
        }
        else if(p->kind == ARG)
        {
            fprintf(fp, "ARG ");
            printOperand(p->codeinfo.singleop.op, fp);
        }
        else if(p->kind == CALL)
        {
            printOperand(p->codeinfo.doubleop.op1, fp);
            fprintf(fp, " := CALL ");
            printOperand(p->codeinfo.doubleop.op2, fp);
        }
        else if(p->kind == PARAM)
        {
            fprintf(fp, "PARAM ");
            printOperand(p->codeinfo.singleop.op, fp);
        }
        else if(p->kind == READ)
        {
            fprintf(fp, "READ ");
            printOperand(p->codeinfo.singleop.op, fp);
        }
        else if(p->kind == WRITE)
        {
            fprintf(fp, "WRITE ");
            printOperand(p->codeinfo.singleop.op, fp);
        }
        fprintf(fp, "\n");
    }
}

//generating intercode
void generate_intercode(TreeNode *root, FILE *fp)
{
    if(errorsum != 0)
        return;
    if(root == NULL)
        return;
    initialize();
    extdeflist_intercode(root->children[0]);
	if(errorsum == 0)
    	printIntercode(listhead, fp);
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
        clearparalist();
    }
}

void fundec_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter fundec_intercode\n");
    //intercode: FUNCTION x
    InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
    Operand *operand = (Operand*)malloc(sizeof(Operand));
    operand->kind = FUNCTION_OP;
    strcpy(operand->opinfo.contents, p->children[0]->contents);
    intercode->kind = FUNCTION_IC;
    intercode->codeinfo.singleop.op = operand;
    insertintercode(intercode);
    if(p->childrennum == 4) //ID LP VarList RP
        varlist_intercode(p->children[2]);
    if(printnode_intercode == 1)
        printf("leave fundec_intercode\n");
}

void varlist_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter varlist_intercode\n");
    paramdec_intercode(p->children[0]);
    if(p->childrennum == 3) //ParamDec COMMA VarList
        varlist_intercode(p->children[2]);
    if(printnode_intercode == 1)
        printf("leave varlist_intercode\n");   
}

void paramdec_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter paramdec_intercode\n");
    funcvardec_intercode(p->children[1]);
    if(printnode_intercode == 1)
        printf("leave paramdec_intercode\n");
}

void funcvardec_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter funcvardec_intercode\n");
    if(p->childrennum > 1)
    {
        if(errorsum == 0)
            printf("Cannot translate: Code contains variables of multi-dimensional array type or parameters of array type.\n");
        errorsum++;
    }
    else
    {
        HashNode *node = findsymbol(p->children[0]->contents, BASIC);
        if(node == NULL)
            node = findsymbol(p->children[0]->contents, STRUCT);
        if(node == NULL)
            node = findsymbol(p->children[0]->contents, ARRAY);
        if(node != NULL)
        {
            InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
            Operand *operand = (Operand*)malloc(sizeof(Operand));
            operand->kind = VARIABLE;
            strcpy(operand->opinfo.contents, p->children[0]->contents);
            intercode->kind = PARAM;
            intercode->codeinfo.singleop.op = operand;
            insertintercode(intercode);
            if(node->typeinfo->kind == STRUCT)
                insertparalist(node->name);
        }
    }
    if(printnode_intercode == 1)
        printf("leave funcvardec_intercode\n");
}

void compst_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter compst_intercode\n");
    funcdeflist_intercode(p->children[1]);
    stmtlist_intercode(p->children[2]);
    if(printnode_intercode == 1)
        printf("leave compst_intercode\n");
}

void funcdeflist_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter funcdeflist_intercode\n");
    if(p != NULL)
    {
        funcdef_intercode(p->children[0]);
        funcdeflist_intercode(p->children[1]);
    }
    if(printnode_intercode == 1)
        printf("leave funcdeflist_intercode\n");
}

void funcdef_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter funcdef_intercode\n");
    funcdeclist_intercode(p->children[1]);
    if(printnode_intercode == 1)
        printf("leave funcdef_intercode\n");
}

void funcdeclist_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter funcdeclist_intercode\n");
    funcdec_intercode(p->children[0]);
    if(p->childrennum == 3)
        funcdeclist_intercode(p->children[2]);
    if(printnode_intercode == 1)
        printf("leave funcdeclist_intercode\n");
}

void funcdec_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter funcdec_intercode\n");
    if(p->childrennum == 1)
    {
        vardec_intercode(p->children[0]);
    }
    else //VarDec ASSIGNOP Exp
    {
        if(p->children[0]->childrennum > 1) //initialize array
        {
            if(errorsum == 0)
                printf("Cannot translate: Try to initialize array at line %d.\n", p->children[0]->linenumber);
            errorsum++;
        }
        else
        {
            Operand *tempvar = newOperand(TEMP_VARIABLE);
            exp_intercode(p->children[2], tempvar);
            InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
            Operand *leftvalue = (Operand*)malloc(sizeof(Operand));
            leftvalue->kind = VARIABLE;
            strcpy(leftvalue->opinfo.contents, p->children[0]->children[0]->contents);
            intercode->kind = ASSIGN;
            intercode->codeinfo.doubleop.op1 = leftvalue;
            intercode->codeinfo.doubleop.op2 = tempvar;
            insertintercode(intercode);
            //wxy do at line 645
            /*if(t1->kind==VAR_CONS||t1->kind==CONSTANT)
                insert_VarconsList(left->u.value,t1->u.var_no);*/
        }
    }
    if(printnode_intercode == 1)
        printf("leave funcdec_intercode\n");
}

void vardec_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter vardec_intercode\n");
    if(p->childrennum == 1) //ID
    {
        HashNode *node = findsymbol(p->children[0]->contents, BASIC);
        if(node == NULL)
        {
            HashNode *node = findsymbol(p->children[0]->contents, STRUCT);
            int size = calculatesize(node->typeinfo);
            InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
            intercode->kind = DEC;
            Operand *operand = (Operand*)malloc(sizeof(Operand));
            operand->kind = VARIABLE;
            strcpy(operand->opinfo.contents, node->name);
            intercode->codeinfo.dec.op = operand;
            intercode->codeinfo.dec.size = size;
            insertintercode(intercode);
        }
    }
    else
    {
        if(p->children[0]->childrennum > 1)
        {
            if(errorsum == 0)
                printf("Cannot translate: Code contains variables of multi-dimensional array type or parameters of array type.\n");
            errorsum++;
        }
        else
        {
            HashNode *node = findsymbol(p->children[0]->children[0]->contents, ARRAY);
            int size = calculatesize(node->typeinfo);
            InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
            intercode->kind = DEC;
            Operand *operand = (Operand*)malloc(sizeof(Operand));
            operand->kind = VARIABLE;
            strcpy(operand->opinfo.contents, node->name);
            intercode->codeinfo.dec.op = operand;
            intercode->codeinfo.dec.size = size;
            insertintercode(intercode);
        }
    }
    if(printnode_intercode == 1)
        printf("leave vardec_intercode\n");
}

void stmtlist_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter stmtlist_intercode\n");
    if(p != NULL)
    {
        stmt_intercode(p->children[0]);
        stmtlist_intercode(p->children[1]);
    }
    if(printnode_intercode == 1)
        printf("leave stmtlist_intercode\n");
}

void stmt_intercode(TreeNode *p)
{
    if(printnode_intercode == 1)
        printf("enter stmt_intercode\n");
    if(p->childrennum == 1) //CompSt
		compst_intercode(p->children[0]);
	else if(p->childrennum == 2) //Exp SEMI
    {
        // Operand *operand = (Operand*)malloc(sizeof(Operand));
        // operand->kind = DEFAULT;
        Operand *operand = newOperand(TEMP_VARIABLE);
        exp_intercode(p->children[0], operand);
    }
	else if(p->childrennum == 3) //RETURN Exp SEMI
	{
		Operand *operand = newOperand(TEMP_VARIABLE);
        exp_intercode(p->children[1], operand);
        InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
        intercode->kind = RETURN;
        intercode->codeinfo.singleop.op = operand;
        insertintercode(intercode);
	}
	else if(p->childrennum == 5)
	{
		if(strcmp(p->children[0]->contents, "if") == 0) //IF LP Exp RP Stmt
		{
			Operand *label1 = newOperand(LABEL_OP);
            Operand *label2 = newOperand(LABEL_OP);
            cond_intercode(p->children[2], label1, label2);
            InterCode *intercode1 = (InterCode*)malloc(sizeof(InterCode));
            intercode1->kind=LABEL_IC;
            intercode1->codeinfo.singleop.op=label1;
            insertintercode(intercode1);
            stmt_intercode(p->children[4]);
            InterCode *intercode2 = (InterCode*)malloc(sizeof(InterCode));
            intercode2->kind=LABEL_IC;
            intercode2->codeinfo.singleop.op=label2;
            insertintercode(intercode2);
		}
		else //WHILE LP Exp RP Stmt
		{
			Operand *label1 = newOperand(LABEL_OP);
            Operand *label2 = newOperand(LABEL_OP);
            Operand *label3 = newOperand(LABEL_OP);
            InterCode *intercode1 = (InterCode*)malloc(sizeof(InterCode));
            intercode1->kind=LABEL_IC;
            intercode1->codeinfo.singleop.op=label1;
            insertintercode(intercode1);
            cond_intercode(p->children[2], label2, label3);
            InterCode *intercode2 = (InterCode*)malloc(sizeof(InterCode));
            intercode2->kind=LABEL_IC;
            intercode2->codeinfo.singleop.op=label2;
            insertintercode(intercode2);
            stmt_intercode(p->children[4]);
            Operand *copylabel1 = copyLabel(label1);
            InterCode *intercodegoto = (InterCode*)malloc(sizeof(InterCode));
            intercodegoto->kind=GOTO;
            intercodegoto->codeinfo.singleop.op=copylabel1;
            insertintercode(intercodegoto);
            InterCode *intercode3 = (InterCode*)malloc(sizeof(InterCode));
            intercode3->kind=LABEL_IC;
            intercode3->codeinfo.singleop.op=label3;
            insertintercode(intercode3);
		}
	}
	else //IF LP Exp RP Stmt ELSE Stmt
	{
		Operand *label1 = newOperand(LABEL_OP);
        Operand *label2 = newOperand(LABEL_OP);
        Operand *label3 = newOperand(LABEL_OP);
        //code1
        cond_intercode(p->children[2], label1, label2);
        //LABEL label1
        InterCode *intercode1 = (InterCode*)malloc(sizeof(InterCode));
        intercode1->kind=LABEL_IC;
        intercode1->codeinfo.singleop.op=label1;
        insertintercode(intercode1);
        //code2
        stmt_intercode(p->children[4]);
        //GOTO label3
        Operand *copylabel3 = copyLabel(label3);
        InterCode *intercodegoto = (InterCode*)malloc(sizeof(InterCode));
        intercodegoto->kind=GOTO;
        intercodegoto->codeinfo.singleop.op=copylabel3;
        insertintercode(intercodegoto);
        //LABEL label2
        InterCode *intercode2 = (InterCode*)malloc(sizeof(InterCode));
        intercode2->kind=LABEL_IC;
        intercode2->codeinfo.singleop.op=label2;
        insertintercode(intercode2);
        //code3
        stmt_intercode(p->children[6]);
        //LABEL label3
        InterCode *intercode3 = (InterCode*)malloc(sizeof(InterCode));
        intercode3->kind=LABEL_IC;
        intercode3->codeinfo.singleop.op=label3;
        insertintercode(intercode3);
	}
    if(printnode_intercode == 1)
        printf("leave stmt_intercode\n");
}

void cond_intercode(TreeNode *p, Operand *label_true, Operand *label_false)
{
    if(printnode_intercode == 1)
        printf("enter cond_intercode %d\n", p->linenumber);
    if(p->childrennum < 1)
    {
        if(printnode_intercode == 1)
            printf("leave cond_intercode %d\n", p->linenumber);
        return;
    }
    if(p->childrennum == 1)
    {
        Operand *tempvar = newOperand(TEMP_VARIABLE);
        //code1
        exp_intercode(p, tempvar);
        //code2
        Operand *constant = (Operand*)malloc(sizeof(Operand));
        constant->kind = CONSTANT;
        constant->opinfo.constant_value = 0;
        InterCode *intercoderelop = (InterCode*)malloc(sizeof(InterCode));
        intercoderelop->kind = RELOPGOTO;
        intercoderelop->codeinfo.relopgoto.x = tempvar;
        intercoderelop->codeinfo.relopgoto.y = constant;
        Operand *copylabeltrue = copyLabel(label_true);
        intercoderelop->codeinfo.relopgoto.z = copylabeltrue;
        strcpy(intercoderelop->codeinfo.relopgoto.relop, "!=");
        insertintercode(intercoderelop);
        //GOTO label_false
        Operand *copylabelfalse = copyLabel(label_false);
        InterCode *intercodegoto = (InterCode*)malloc(sizeof(InterCode));
        intercodegoto->kind=GOTO;
        intercodegoto->codeinfo.singleop.op=copylabelfalse;
        insertintercode(intercodegoto);
        if(printnode_intercode == 1)
            printf("leave cond_intercode %d\n", p->linenumber);
        return;
    }
    if(strcmp(p->children[0]->type, "NOT") == 0) //NOT Exp
    {
        cond_intercode(p->children[1], label_false, label_true);
    }
    else if(strcmp(p->children[1]->type, "RELOP") == 0) //Exp RELOP Exp
    {
        Operand *tempvar1 = newOperand(TEMP_VARIABLE);
        Operand *tempvar2 = newOperand(TEMP_VARIABLE);
        //code1
        exp_intercode(p->children[0], tempvar1);
        //code2
        exp_intercode(p->children[2], tempvar2);
        //code3
        InterCode *intercoderelop = (InterCode*)malloc(sizeof(InterCode));
        intercoderelop->kind=RELOPGOTO;
        intercoderelop->codeinfo.relopgoto.x = tempvar1;
        intercoderelop->codeinfo.relopgoto.y = tempvar2;
        Operand *copylabletrue = copyLabel(label_true);
        intercoderelop->codeinfo.relopgoto.z = copylabletrue;
        strcpy(intercoderelop->codeinfo.relopgoto.relop, p->children[1]->contents);
        insertintercode(intercoderelop);
        //GOTO label_false
        Operand *copylabelfalse = copyLabel(label_false);
        InterCode *intercodegoto = (InterCode*)malloc(sizeof(InterCode));
        intercodegoto->kind=GOTO;
        intercodegoto->codeinfo.singleop.op=copylabelfalse;
        insertintercode(intercodegoto);
    }
    else if(strcmp(p->children[1]->type, "AND") == 0) //Exp AND Exp
    {
        Operand *label1 = newOperand(LABEL_OP);
        //code1
        cond_intercode(p->children[0], label1, label_false);
        //LABEL label1
        InterCode *intercode1 = (InterCode*)malloc(sizeof(InterCode));
        intercode1->kind=LABEL_IC;
        intercode1->codeinfo.singleop.op=label1;
        insertintercode(intercode1);
        //code2
        cond_intercode(p->children[2], label_true, label_false);
    }
    else if(strcmp(p->children[1]->type, "OR") == 0) //Exp OR Exp
    {
        Operand *label1 = newOperand(LABEL_OP);
        //code1
        cond_intercode(p->children[0], label_true, label1);
        //LABEL label1
        InterCode *intercode1 = (InterCode*)malloc(sizeof(InterCode));
        intercode1->kind=LABEL_IC;
        intercode1->codeinfo.singleop.op=label1;
        insertintercode(intercode1);
        //code2
        cond_intercode(p->children[2], label_true, label_false);
    }
    else
    {
        Operand *tempvar = newOperand(TEMP_VARIABLE);
        //code1
        exp_intercode(p, tempvar);
        //code2
        Operand *constant = (Operand*)malloc(sizeof(Operand));
        constant->kind = CONSTANT;
        constant->opinfo.constant_value = 0;
        InterCode *intercoderelop = (InterCode*)malloc(sizeof(InterCode));
        intercoderelop->kind = RELOPGOTO;
        intercoderelop->codeinfo.relopgoto.x = tempvar;
        intercoderelop->codeinfo.relopgoto.y = constant;
        Operand *copylabeltrue = copyLabel(label_true);
        intercoderelop->codeinfo.relopgoto.z = copylabeltrue;
        strcpy(intercoderelop->codeinfo.relopgoto.relop, "!=");
        insertintercode(intercoderelop);
        //GOTO label_false
        Operand *copylabelfalse = copyLabel(label_false);
        InterCode *intercodegoto = (InterCode*)malloc(sizeof(InterCode));
        intercodegoto->kind=GOTO;
        intercodegoto->codeinfo.singleop.op=copylabelfalse;
        insertintercode(intercodegoto);
    }
    if(printnode_intercode == 1)
        printf("leave cond_intercode %d\n", p->linenumber);
}

void exp_intercode(TreeNode *p, Operand *op)
{
    if(printnode_intercode == 1)
        printf("enter exp_intercode\n");
    if(p->childrennum == 1)
    {
        if(strcmp(p->children[0]->type, "ID") == 0)
			return expid_intercode(p, op);
        else if(strcmp(p->children[0]->type, "INT") == 0)
			return expint_intercode(p, op);
    }
	else if(p->childrennum == 2)
	{
		if (strcmp(p->children[0]->type, "MINUS") == 0)
			return minusexp_intercode(p, op);
		else
			return boolexp_intercode(p, op);
	}
	else if(p->childrennum == 3)
	{
		if (strcmp(p->children[0]->type, "LP") == 0)// LP Exp RP
			return exp_intercode(p->children[1], op);
		else if (strcmp(p->children[0]->type, "ID") == 0)// ID LP RP
			return callfunc_intercode(p, op);
		else // Exp ...
		{
			if (strcmp(p->children[1]->type, "ASSIGNOP") == 0)
				return expassignop_intercode(p, op);
			else if (strcmp(p->children[0]->type, "AND") == 0 || strcmp(p->children[0]->type, "OR") == 0)
				return boolexp_intercode(p, op);
			else if (strcmp(p->children[1]->type, "DOT") == 0)
				return callstruct_intercode(p, op);
			else if (strcmp(p->children[1]->type, "RELOP") == 0)
				return boolexp_intercode(p, op);
			else //PLUS, MINUS, STAR, DIV
				return expcalculate_intercode(p, op);
		}
	}
	else
	{
		if(strcmp(p->children[0]->type, "ID") == 0)// ID LP Args RP
			return callfunc_intercode(p, op);
		else // Exp LB Exp RB
			return callarray_intercode(p, op);
	}
    if(printnode_intercode == 1)
        printf("leave exp_intercode\n");
}

void expid_intercode(TreeNode *p, Operand *op)
{
    if(printnode_intercode == 1)
        printf("enter expid_intercode\n");
    int ret1 = checksymbol(p->children[0]->contents, 0);
    int ret2 = checksymbol(p->children[0]->contents, 1);
    if(ret1 == 0 && ret2 == 0)
        return;
    op->kind = VARIABLE;
    strcpy(op->opinfo.contents, p->children[0]->contents);
    if(printnode_intercode == 1)
        printf("leave exp_intercode\n");
}

void expint_intercode(TreeNode *p, Operand *op)
{
    if(printnode_intercode == 1)
        printf("enter expint_intercode\n");
    op->kind = CONSTANT;
    op->opinfo.constant_value = atoi(p->children[0]->contents);
    if(printnode_intercode == 1)
        printf("leave expint_intercode\n");
}

void minusexp_intercode(TreeNode *p, Operand *op)
{
    if(printnode_intercode == 1)
        printf("enter minusexp_intercode\n");
    Operand *tempvar = newOperand(TEMP_VARIABLE);
    Operand *copyop = copyOperand(op);
    //code1
    exp_intercode(p->children[1],tempvar);
    //code2
    InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
    intercode->kind = SUB;
    Operand *constant = (Operand*)malloc(sizeof(Operand));
    constant->kind = CONSTANT;
    constant->opinfo.constant_value = 0;
    intercode->codeinfo.tripleop.op1=constant;
    intercode->codeinfo.tripleop.op2=tempvar;
    intercode->codeinfo.tripleop.op=copyop;
    insertintercode(intercode);
    if(printnode_intercode == 1)
        printf("leave minusexp_intercode\n");
}

void boolexp_intercode(TreeNode *p, Operand *op)//NOT AND OR RELOP
{
	if(printnode_intercode == 1)
        printf("enter boolexp_intercode\n");
    Operand *copyop1 = copyOperand(op);
    Operand *label1 = newOperand(LABEL_OP);
    Operand *label2 = newOperand(LABEL_OP);
	Operand *constant_zero = (Operand*)malloc(sizeof(Operand));
    constant_zero->kind = CONSTANT;
    constant_zero->opinfo.constant_value = 0;
	//code0
	InterCode *intercode0 = (InterCode*)malloc(sizeof(InterCode));
    intercode0->kind = ASSIGN;
	intercode0->codeinfo.doubleop.op1=copyop1;
	intercode0->codeinfo.doubleop.op2=constant_zero;
	insertintercode(intercode0);
	//code1
	cond_intercode(p,label1,label2);
	//LABEL label1
	InterCode *interlabel1 = (InterCode*)malloc(sizeof(InterCode));
    interlabel1->kind=LABEL_IC;
    interlabel1->codeinfo.singleop.op=label1;
    insertintercode(interlabel1);
	//code2
    Operand *copyop2 = copyOperand(op);
	Operand *constant_one = (Operand*)malloc(sizeof(Operand));
    constant_one->kind = CONSTANT;
    constant_one->opinfo.constant_value = 1;
	InterCode *intercode2 = (InterCode*)malloc(sizeof(InterCode));
    intercode2->kind = ASSIGN;
	intercode2->codeinfo.doubleop.op1=copyop2;
	intercode2->codeinfo.doubleop.op2=constant_one;
	insertintercode(intercode2);
	//LABEL label2
	InterCode *interlabel2 = (InterCode*)malloc(sizeof(InterCode));
    interlabel2->kind=LABEL_IC;
    interlabel2->codeinfo.singleop.op=label2;
    insertintercode(interlabel2);
	if(printnode_intercode == 1)
        printf("leave boolexp_intercode\n");
}

void expassignop_intercode(TreeNode *p, Operand *op)
{
	if(printnode_intercode == 1)
        printf("enter expassignop_intercode\n");
	Operand *tempvar1 = newOperand(TEMP_VARIABLE);
	exp_intercode(p->children[0],tempvar1);
	//code1
	Operand *tempvar2 = newOperand(TEMP_VARIABLE);
	exp_intercode(p->children[2],tempvar2);
	TypeInfo *type1 = Exp(p->children[0]);
	TypeInfo *type2 = Exp(p->children[2]);
	if(type1->kind==ARRAY&&type2->kind==ARRAY)
	{
		tempvar1->kind=ADDRESS;
		tempvar2->kind=ADDRESS;
		Operand *temp1 = newOperand(TEMP_VARIABLE);
		Operand *temp2 = newOperand(TEMP_VARIABLE);
		int elementsize = calculatesize(type1->info.array.element);
		int size1=type1->info.array.size;
		int size2=type2->info.array.size;
		int arraysize;
		if(size1<size2)
			arraysize=size1;
		else
			arraysize=size2;
		for(int i=0;i<arraysize;i++){
			Operand *constant_size =(Operand*)malloc(sizeof(Operand));
    			constant_size->kind = CONSTANT;
    			constant_size->opinfo.constant_value = i*elementsize;
			InterCode *tempcode1 = (InterCode*)malloc(sizeof(InterCode));
    			tempcode1->kind = PLUS;
			tempcode1->codeinfo.tripleop.op=temp1;
			tempcode1->codeinfo.tripleop.op1=copyOperand(tempvar1);
			tempcode1->codeinfo.tripleop.op2=constant_size;
			insertintercode(tempcode1);
			InterCode *tempcode2 = (InterCode*)malloc(sizeof(InterCode));
    			tempcode2->kind = PLUS;
			tempcode2->codeinfo.tripleop.op=temp2;
			tempcode2->codeinfo.tripleop.op1=copyOperand(tempvar2);
			tempcode2->codeinfo.tripleop.op2=constant_size;
			insertintercode(tempcode2);
			temp1->kind=STAR;
			temp2->kind=STAR;
			InterCode *arraycode = (InterCode*)malloc(sizeof(InterCode));
    			arraycode->kind = ASSIGN;
			arraycode->codeinfo.doubleop.op1=copyOperand(temp1);
			arraycode->codeinfo.doubleop.op2=copyOperand(temp2);
			insertintercode(arraycode);
			temp1->kind=VARIABLE;
			temp2->kind=VARIABLE;
		}
		tempvar1->kind=VARIABLE;
		tempvar2->kind=VARIABLE;

	}
	else
	{
		//code2 [variable.name:=t1]
		InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
	    	intercode->kind = ASSIGN;
		intercode->codeinfo.doubleop.op1=tempvar1;
		intercode->codeinfo.doubleop.op2=tempvar2;
		insertintercode(intercode);
	}
	//code2 [place:=variable.name]
	op->kind=tempvar1->kind;
	strcpy(op->opinfo.contents, tempvar1->opinfo.contents);
	if(printnode_intercode == 1)
        printf("leave expassignop_intercode\n");
}

void expcalculate_intercode(TreeNode *p, Operand *op)
{
	if(printnode_intercode == 1)
        printf("enter expcalculate_intercode\n");
	Operand *tempvar1 = newOperand(TEMP_VARIABLE);
	Operand *tempvar2 = newOperand(TEMP_VARIABLE);
	//code1
	exp_intercode(p->children[0],tempvar1);
	//code2
	exp_intercode(p->children[2],tempvar2);
	InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
	if(strcmp(p->children[1]->type,"PLUS")==0)
		intercode->kind=PLUS;
	else if(strcmp(p->children[1]->type,"MINUS")==0)
		intercode->kind=SUB;
	else if(strcmp(p->children[1]->type,"STAR")==0)
		intercode->kind=MUL;
	else if(strcmp(p->children[1]->type,"DIV")==0)
		intercode->kind=DIV;
    Operand *copyop = copyOperand(op);
	intercode->codeinfo.tripleop.op=copyop;
	intercode->codeinfo.tripleop.op1=tempvar1;
	intercode->codeinfo.tripleop.op2=tempvar2;
	insertintercode(intercode);
	if(printnode_intercode == 1)
        printf("leave expcalculate_intercode\n");
}

void callarray_intercode(TreeNode *p, Operand *op) //Exp LB Exp RB
{
    if(printnode_intercode == 1)
        printf("enter callarray_intercode\n");
    Operand *lbrb = newOperand(TEMP_VARIABLE);
    exp_intercode(p->children[2], lbrb);
    Operand *exp1 = newOperand(TEMP_VARIABLE);
    exp_intercode(p->children[0], exp1);

    if(exp1->kind == STAR)
        exp1->kind = VARIABLE;
    else
        exp1->kind = ADDRESS;
    
    InterCode *caladdr = (InterCode*)malloc(sizeof(InterCode));
    caladdr->kind = PLUS;

    Operand *copyop = copyOperand(op);
    copyop->kind = TEMP_VARIABLE;
    caladdr->codeinfo.tripleop.op = copyop;
    caladdr->codeinfo.tripleop.op1 = exp1;

    TypeInfo *type = Exp(p->children[0]);
    int elementsize = calculatesize(type->info.array.element);

    if(lbrb->kind == CONSTANT)
    {
        lbrb->opinfo.constant_value = lbrb->opinfo.constant_value * elementsize;
        caladdr->codeinfo.tripleop.op2 = lbrb;
    }
    else
    {
        InterCode *caloffset = (InterCode*)malloc(sizeof(InterCode));
        caloffset->kind = MUL;

        Operand *constant = (Operand*)malloc(sizeof(Operand));
        constant->kind = CONSTANT;
        constant->opinfo.constant_value = elementsize;

        Operand *tempvar = newOperand(TEMP_VARIABLE);

        caloffset->codeinfo.tripleop.op = tempvar;
        caloffset->codeinfo.tripleop.op1 = lbrb;
        caloffset->codeinfo.tripleop.op2 = constant;
        insertintercode(caloffset);

        caladdr->codeinfo.tripleop.op2 = tempvar;
    }
    insertintercode(caladdr);
    op->kind = STAR;

    if(printnode_intercode == 1)
        printf("leave callarray_intercode\n");
}

void callstruct_intercode(TreeNode *p, Operand *op) //Exp DOT ID
{
    if(printnode_intercode == 1)
        printf("enter callstruct_intercode\n");

    Operand *exp1 = newOperand(TEMP_VARIABLE);
    exp_intercode(p->children[0], exp1);
    // Operand *fieldname = (Operand*)malloc(sizeof(Operand));
    // fieldname->kind = VARIABLE;
    // strcpy(fieldname->opinfo.contents, p->children[2]->contents);
    TypeInfo *type = Exp(p->children[0]);
    int size = 0;
    FieldList *list = type->info.structure;
    while(list != NULL)
    {
        if(strcmp(list->name, p->children[2]->contents)==0)
            break;
        else
        {
            size += calculatesize(list->typeinfo);
            list = list->next;
        }
    }

    if(exp1->kind == STAR)
        exp1->kind = VARIABLE;
    else if(exp1->kind != CONSTANT && structisparameter(exp1->opinfo.contents) == 1)
        exp1->kind = VARIABLE;  
    else
        exp1->kind = ADDRESS;
    
    Operand *operand = copyOperand(op);
    operand->kind = TEMP_VARIABLE;
    InterCode *caladdr = (InterCode*)malloc(sizeof(InterCode));
    caladdr->kind = PLUS;
    caladdr->codeinfo.tripleop.op = operand;
    caladdr->codeinfo.tripleop.op1 = exp1;
    Operand *constant = (Operand*)malloc(sizeof(Operand));
    constant->kind = CONSTANT;
    constant->opinfo.constant_value = size;
    caladdr->codeinfo.tripleop.op2 = constant;
    insertintercode(caladdr);
    op->kind = STAR;

    if(printnode_intercode == 1)
        printf("leave callstruct_intercode\n");
}

void callfunc_intercode(TreeNode *p, Operand *op)
{
	if(printnode_intercode == 1)
        printf("enter callfunc_intercode\n");
	int ret1 = checksymbol(p->children[0]->contents, 1);
	if(ret1 == 0)
		return;
	else
	{
        Operand *copyop = copyOperand(op);
		if(p->childrennum == 3)//ID LP RP
		{
			if(strcmp(p->children[0]->contents,"read")==0)
			{
				InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
    			intercode->kind = READ;
				intercode->codeinfo.singleop.op = copyop;
				insertintercode(intercode);
			
			}
			else
			{
				Operand *fun = (Operand*)malloc(sizeof(Operand));
				fun->kind=FUNCTION_OP;
				strcpy(fun->opinfo.contents,p->children[0]->contents);
				InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
    			intercode->kind = CALL;
				intercode->codeinfo.doubleop.op1=copyop;
				intercode->codeinfo.doubleop.op2=fun;
				insertintercode(intercode);
			}
		}
		else//ID LP Args RP
		{
			Args *args = arg_intercode(p->children[2]);
			if(strcmp(p->children[0]->contents,"write")==0)
			{
				InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
    			intercode->kind = WRITE;
				intercode->codeinfo.singleop.op=args->one_arg;
				insertintercode(intercode);
			}	
			else
			{
				while(args != NULL)
				{
					InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
					intercode->kind=ARG;
					intercode->codeinfo.singleop.op=args->one_arg;
					insertintercode(intercode);
					args=args->next;
				}
				Operand *fun = (Operand*)malloc(sizeof(Operand));
				fun->kind=FUNCTION_OP;
				strcpy(fun->opinfo.contents,p->children[0]->contents);
				InterCode *intercode = (InterCode*)malloc(sizeof(InterCode));
    			intercode->kind = CALL;
				intercode->codeinfo.doubleop.op1=copyop;
				intercode->codeinfo.doubleop.op2=fun;
				insertintercode(intercode);
			}		
			
		}
	}
	if(printnode_intercode == 1)
        printf("leave callfunc_intercode\n");

}

Args* arg_intercode(TreeNode *p)
{
	if(printnode_intercode == 1)
        printf("enter arg_intercode\n");
	Args *args = NULL;
    TreeNode *q = p;
	while(q->childrennum > 1) //Exp COMMA Args
	{
		Operand *tempvar = newOperand(TEMP_VARIABLE);
		exp_intercode(q->children[0],tempvar);
		TypeInfo *type = Exp(q->children[0]);
		if(type->kind == STRUCT)
			tempvar->kind = ADDRESS;
		Args *arg=(Args*)malloc(sizeof(Args));
		arg->one_arg=tempvar;
		arg->next=args;
		args=arg;
		q = q->children[2];
	}
	Operand *tempvar = newOperand(TEMP_VARIABLE);
	exp_intercode(q->children[0],tempvar);
	TypeInfo *type = Exp(q->children[0]);
	if(type->kind == STRUCT)
		tempvar->kind=ADDRESS;
	Args *arg = (Args*)malloc(sizeof(Args));
	arg->one_arg = tempvar;
	arg->next = args;
	args = arg;
    if(printnode_intercode == 1)
        printf("leave arg_intercode\n");
	return args;
}
