#include "semantic.h"

extern int errorsum;

int anonymous;
int printnote = 0;

void initsymboltable()
{
    structnametable = NULL;
    for(int i=0; i<=HASH_NUMBER; i++)
        symboltable[i] = NULL;

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
    strcpy(paralist->name, "__WRITE_FUNC_PARAMETER__");
    paralist->linenumber = -1;
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
}

int hash_func(char *name) 
{
    unsigned int val = 0, i;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if (i = val & ~HASH_NUMBER) val = (val ^ (i >> 12)) & HASH_NUMBER;
    }
    return (int)val;
}

HashNode* findsymbol(char *name, Kind kind)
{
    char hashname[33];
    strcpy(hashname, name);
    int index=hash_func(hashname);
    HashNode *p=symboltable[index];
    int find=0;
    while(p != NULL)
    {
        if(strcmp(p->name, name)==0)
        {
            if(p->typeinfo->kind==kind)
                return p;
        }
        p = p->next;
    }
    return p;
}

int checksymbol(char *name, int isfunc)
{
    char hashname[33];
    strcpy(hashname, name);
    int index=hash_func(name);
    HashNode *p=symboltable[index];
    int find=0;
    while(p!=NULL)
    {
        if(strcmp(p->name, name)==0)
        {
            if(isfunc==0)
            {
                if(p->typeinfo->kind!=FUNC)
                {
                    find=1;
                    break;
                }
            }
            else
            {
                if(p->typeinfo->kind==FUNC)
                {
                    find=1;
                    break;
                }
            }
        }
        p = p->next;
    }
    return find;
}

void insertsymbol(HashNode *node)
{
    char hashname[33];
    strcpy(hashname, node->name);
    int index = hash_func(hashname);
    node->next = symboltable[index];
    symboltable[index] = node;
}

void printnodeinfo(HashNode *node)
{
    printf("hash node name: %s\n", node->name);
    printTypeInfo(node->typeinfo);
}


//supplement tool function
void printTypeInfo(TypeInfo *type)
{
    if(type == NULL)
    {
        printf("type is NULL\n");
        return;
    }
    if(type->kind == BASIC)
    {
        printf("type: basic ");
        if(type->info.basic == TYPE_INT)
            printf("int\n");
        else
            printf("float\n");
    }
    else if(type->kind == ARRAY)
    {
        printf("type: array, size: %d\n", type->info.array.size);
        printTypeInfo(type->info.array.element);
    }
    else if(type->kind == STRUCT)
    {
        printf("type: structure\n");
        printStruct(type->info.structure);
        printf("end of the structure\n");
    }
    else if(type->kind == FUNC)
    {
        printf("type: function\n");
		printFunc(type->info.function);
		printf("end of the function\n");
    }
    else
    {
        printf("type: error %d\n", type->info.errortype);
    }
}

void printStruct(FieldList *field)
{
    if(field == NULL)
    {
        printf("field is NULL\n");
        return;
    }
    printf("field: name: %s at line: %d\n", field->name, field->linenumber);
    printTypeInfo(field->typeinfo);
    printStruct(field->next);
}

void printFunc(Function *func)
{
	printf("function: paramnum: %d\n", func->paranum);
	printParameterList(func->paralist);
	printTypeInfo(func->functype);
}

void printParameterList(ParameterList *param)
{
	if (param == NULL)
	{
		printf("param is NULL\n");
		return;
	}
	printf("param: name %s\n", param->name);
	printTypeInfo(param->typeinfo);
	printParameterList(param->next);
}

void copyTypeInfo(TypeInfo *type, TypeInfo *copytype) //type <-- copytype
{
    type->kind=copytype->kind;
    if(copytype->kind==BASIC)
        type->info.basic=copytype->info.basic;
    else if(copytype->kind==ARRAY)
    {
        type->info.array.size = copytype->info.array.size;
        type->info.array.element = (TypeInfo*)malloc(sizeof(TypeInfo));
        copyTypeInfo(type->info.array.element, copytype->info.array.element);
    }
    else if(copytype->kind==STRUCT)
    {
		if(copytype->info.structure == NULL)
		{
			type->info.structure = NULL;
		}
		else
        {
			type->info.structure=(FieldList*)malloc(sizeof(struct FieldList));
        	copyStruct(type->info.structure, copytype->info.structure);
		}
    }
    else if(copytype->kind==FUNC)
    {
        type->info.function = (Function*)malloc(sizeof(Function));
        copyFunc(type->info.function, copytype->info.function);
    }
    else
        type->info.errortype=copytype->info.errortype;
}

void copyStruct(FieldList *list, FieldList *copylist) //list <-- copylist
{
    if(copylist==NULL)
    {
        list=NULL;
        return;
    }
    strcpy(list->name, copylist->name);
    list->linenumber = copylist->linenumber;
    list->typeinfo = (TypeInfo*)malloc(sizeof(TypeInfo));
    copyTypeInfo(list->typeinfo, copylist->typeinfo);
    if(copylist->next==NULL)
        list->next=NULL;
    else
    {
        FieldList *nextlist = (FieldList*)malloc(sizeof(struct FieldList));
        copyStruct(nextlist, copylist->next);
        list->next = nextlist;
    }
}

void copyFunc(Function *func, Function *copyfunc)
{
	func->paranum = copyfunc->paranum;
	if(copyfunc->paranum == 0)
	{
		func->paralist = NULL;
	}
	else
	{
		func->paralist = (ParameterList*)malloc(sizeof(ParameterList));
		copyParameterList(func->paralist, copyfunc->paralist);
	}
	func->functype = (TypeInfo*)malloc(sizeof(TypeInfo));
	copyTypeInfo(func->functype, copyfunc->functype);
}

void copyParameterList(ParameterList *param, ParameterList *copyparam)
{
	if(copyparam == NULL)
	{
		param = NULL;
		return;
	}
	strcpy(param->name, copyparam->name);
    param->linenumber = copyparam->linenumber;
	param->typeinfo = (TypeInfo*)malloc(sizeof(TypeInfo));
	copyTypeInfo(param->typeinfo, copyparam->typeinfo);
	if (copyparam->next == NULL)
		param->next = NULL;
	else
	{
		ParameterList *nextparam = (ParameterList*)malloc(sizeof(ParameterList));
		copyParameterList(nextparam, copyparam->next);
		param->next = nextparam;
	}
}

int isEqualType(TypeInfo *a, TypeInfo *b)
{
	if(a->kind != b->kind)
		return 0;
	if(a->kind == BASIC)
	{
		if(a->info.basic == b->info.basic)
			return 1;
		else
			return 0;
	}
	else if(a->kind == ARRAY)
	{
		if(isEqualType(a->info.array.element, b->info.array.element) == 1)
			return 1;
		else
			return 0;
	}
	else if(a->kind == STRUCT)
	{
		if(isEqualStruct(a->info.structure, b->info.structure) == 1)
			return 1;
		else
			return 0;
	}
	else if (a->kind == FUNC)
	{
		if(isEqualFunc(a->info.function, b->info.function) == 1)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int isEqualStruct(FieldList *a, FieldList *b)
{
	if(a==NULL && b==NULL)
		return 1;
	if(a==NULL || b==NULL)
		return 0;
	if(isEqualType(a->typeinfo, b->typeinfo)==1 && isEqualStruct(a->next, b->next)==1)
		return 1;
	else
		return 0;
}

int isEqualFunc(Function *a, Function *b)
{
	return isEqualType(a->functype, b->functype);
}

// Semantic Analysis
void semantic_analysis(TreeNode *root)
{
    if(errorsum != 0)
        return;
    if(root == NULL)
        return;
    initsymboltable();
    anonymous = 1;
    extdeflist(root->children[0]);
}

void extdeflist(TreeNode *p)
{
    if(p == NULL)
        return;
    extdef(p->children[0]);
    extdeflist(p->children[1]);
}

void extdef(TreeNode *p)
{
    TypeInfo *spf=specifier(p->children[0]);
    if(p->childrennum==3)
    {
        if(strcmp(p->children[2]->type, "SEMI")==0)
            extdeclist(p->children[1], spf);
        else
        {
            fundec(p->children[1], spf);
            compst(p->children[2], spf);
        }
    }
}

TypeInfo* specifier(TreeNode *p)
{
    if(printnote==1)
    	printf("specifier\n");
    if(strcmp(p->children[0]->type, "TYPE")==0)
    {
        TypeInfo *type = (TypeInfo*)malloc(sizeof(TypeInfo));
        type->kind=BASIC;
        if(strcmp(p->children[0]->contents, "int")==0)
            type->info.basic=TYPE_INT;
        else
            type->info.basic=TYPE_FLOAT;
        return type;
    }
    else
        return structspecifier(p->children[0]);
    if(printnote==1)
	    printf("end of specifier\n");
}

TypeInfo* structspecifier(TreeNode *p)
{
    //printf("in structspecifier, %d\n", p->childrennum);
    TypeInfo *type = (TypeInfo*)malloc(sizeof(TypeInfo));
    if(p->childrennum==2) //STRUCT Tag
    {
        HashNode *node = findsymbol(p->children[1]->children[0]->contents, STRUCT);
        if(node == NULL)
        {
            //error 17, undefined structure name
            printf("Error type 17 at Line %d: undefined structure name: \"%s\".\n", p->children[1]->children[0]->linenumber, p->children[1]->children[0]->contents);
            type->kind=ERROR;
            type->info.errortype=17;
            errorsum++;
        }
        else
            copyTypeInfo(type, node->typeinfo);
    }
    else //STRUCT OptTag LC DefList RC
    {
        char structname[33]="";
        if(p->children[1]!=NULL)
        {
            strcpy(structname, p->children[1]->children[0]->contents);
            StructName *sname = (StructName*)malloc(sizeof(StructName));
            strcpy(sname->name, structname);
            sname->next = structnametable;
            structnametable = sname;
        }
        else //anonymous structure
        {
            sprintf(structname, "%d", anonymous);
            //printf("anonymous: %s\n", structname);
            anonymous++;
        }
        int ret=checksymbol(structname, 0);
        if(ret != 0)
        {
            //error 16, redefined name
            printf("Error type 16 at Line %d: structure's name: \"%s\" is a redefined name.\n", p->children[1]->linenumber, p->children[1]->children[0]->contents);
            type->kind=ERROR;
            type->info.errortype=16;
            errorsum++;
        }
        else
        {
            HashNode *node = (HashNode*)malloc(sizeof(HashNode));
            FieldList *field = (FieldList*)malloc(sizeof(FieldList));
            field->next = NULL;
            structdeflist(p->children[3], field);
            type->kind = STRUCT;
            type->info.structure = field->next;
            strcpy(node->name, structname);
            node->typeinfo = (TypeInfo*)malloc(sizeof(TypeInfo));
            copyTypeInfo(node->typeinfo, type);
            node->next = NULL;
            insertsymbol(node);
        }
    }
    //printf("out structspecifier\n");
    return type;
}

void structdeflist(TreeNode *p, FieldList *structinfo)
{
    //printf("enter struct deflist\n");
    if(p == NULL)
		return;
    FieldList *def = structdef(p->children[0]);
    //check whether has redefined variable
    FieldList *t = def;
    for(;t!=NULL;t=t->next)
    {
        FieldList *start = t->next;
        for(;start!=NULL;start=start->next)
        {
            if(strcmp(start->name, t->name)==0)
            {
                printf("Error type 15 at Line %d: redefined field name: \"%s\" in structure.\n", start->linenumber, start->name);
                errorsum++;
            }
        }
        // do we need to check all the struct name defined?
        // StructName *head = structnametable;
        // for(;head!=NULL;head=head->next)
        // {
        //     if(strcmp(head->name, t->name)==0)
        //     {
        //         printf("Error type 15 at Line %d: redefined field name: \"%s\" in structure.\n", t->linenumber, t->name);
        //         errorsum++;
        //     }
        // }
        FieldList *fieldhead = structinfo->next;
        for(;fieldhead!=NULL;fieldhead=fieldhead->next)
        {
            if(strcmp(fieldhead->name, t->name)==0)
            {
                printf("Error type 15 at Line %d: redefined field name: \"%s\" in structure.\n", t->linenumber, t->name);
                errorsum++;
            }
        }
    }
    //end checking
    FieldList *q = structinfo;
    while(q->next != NULL)
        q = q->next;
    q->next = def;
    structdeflist(p->children[1], structinfo);
    //printf("leave struct deflist\n");
}

FieldList* structdef(TreeNode *p)
{
    //printf("structdef: type: %s\n", p->children[0]->contents);
    TypeInfo *type = specifier(p->children[0]);
    return structdeclist(p->children[1], type);
    //printf("leave structdef: type: %s\n", p->children[0]->contents);
}

FieldList* structdeclist(TreeNode *p, TypeInfo *type)
{
    if(p->childrennum == 1) //Dec
        return structdec(p->children[0], type);
    else //Dec COMMA DecList
    {
        FieldList *field = structdec(p->children[0], type);
        field->next = structdeclist(p->children[2], type);
        return field;
    }
}

FieldList* structdec(TreeNode *p, TypeInfo *type)
{
    FieldList *field = vardec(p->children[0], type);
    if(p->childrennum != 1) //VarDec ASSIGNOP Exp
    {
        //error 15, initialize variable in structure
        printf("Error type 15 at Line %d: try to initialize variable: \"%s\" in structure.\n", p->children[1]->linenumber, field->name);
        errorsum++;
    }
    return field;
}

FieldList* vardec(TreeNode *p, TypeInfo *type)
{
    if(printnote==1)
		printf("vardec\n");
    TypeInfo *vartype = (TypeInfo*)malloc(sizeof(TypeInfo));
    FieldList *field = (FieldList*)malloc(sizeof(FieldList));
    if(p->childrennum==1) //ID
    {
        copyTypeInfo(vartype, type);
        strcpy(field->name, p->children[0]->contents);
        field->linenumber = p->children[0]->linenumber;
    }
    else //VarDec LB INT RB
    {
        vartype->kind=ARRAY;
        TreeNode *q=p;
        int dimension=0;
        while(q->childrennum!=1)
        {
            dimension++;
            q=q->children[0];
        }
        int *dimsize=(int*)malloc(sizeof(int)*dimension);
        TypeInfo *dimtype[dimension];
        q = p;
        for(int i=0; i<dimension; i++,q=q->children[0])
        {
            int size = atoi(q->children[2]->contents);
            dimsize[i] = size;
            dimtype[i] = (TypeInfo*)malloc(sizeof(TypeInfo));
            if(i == 0)
                copyTypeInfo(dimtype[i], type);
            else
            {
                dimtype[i]->kind = ARRAY;
                dimtype[i]->info.array.size = dimsize[i-1];
                dimtype[i]->info.array.element = dimtype[i-1];
            }
        }
        vartype->info.array.size = dimsize[dimension-1];
        vartype->info.array.element = dimtype[dimension-1];
        strcpy(field->name, q->children[0]->contents);
        field->linenumber = q->children[0]->linenumber;
        free(dimsize);
    }
    field->typeinfo = vartype;
    field->next = NULL;
    if(printnote==1)
		printf("end of vardec\n");
    return field;
}

void extdeclist(TreeNode *p, TypeInfo *type)
{
    if(printnote==1)
		printf("extdeclist\n");
	FieldList *field = vardec(p->children[0], type);
	int ret = checksymbol(field->name, 0);
	if (ret != 0)
	{
		//error 3, redefined variable
		printf("Error type 3 at Line %d: redefined variable name: \"%s\".\n", field->linenumber, field->name);
		errorsum++;
	}
	else
	{
		HashNode *node = (HashNode*)malloc(sizeof(HashNode));
		strcpy(node->name, field->name);
		node->typeinfo = (TypeInfo*)malloc(sizeof(TypeInfo));
		copyTypeInfo(node->typeinfo, field->typeinfo);
		node->next = NULL;
		insertsymbol(node);
	}
	if(p->childrennum == 3) //VarDec COMMA ExtDecList
		extdeclist(p->children[2], type);
    if(printnote==1)
		printf("end of extdeclist\n");
}

void fundec(TreeNode *p, TypeInfo *type)
{
    if(printnote==1)
		printf("fundec\n");
	Function *func = (Function*)malloc(sizeof(Function));
    func->functype = (TypeInfo*)malloc(sizeof(TypeInfo));
	copyTypeInfo(func->functype, type);
	if (p->childrennum == 4) //ID LP VarList RP
    {
        func->paralist = varlist(p->children[2]);
        ParameterList *listhead = func->paralist;
        int cnt = 0;
        for(;listhead!=NULL;listhead=listhead->next,cnt++);
        func->paranum = cnt;
    }
	else //ID LP RP
    {
        func->paralist = NULL;
        func->paranum = 0;
    }
	int ret = checksymbol(p->children[0]->contents, 1);
	if(ret != 0)
	{
		//error 4, redefined function name
		printf("Error type 4 at Line %d: redefined function name: \"%s\".\n", p->children[0]->linenumber, p->children[0]->contents);
		errorsum++;
	}
	else
	{
		HashNode *node = (HashNode*)malloc(sizeof(HashNode));
		strcpy(node->name, p->children[0]->contents);
		node->typeinfo = (TypeInfo*)malloc(sizeof(TypeInfo));
		node->typeinfo->kind = FUNC;
        node->typeinfo->info.function = (Function*)malloc(sizeof(Function));
        copyFunc(node->typeinfo->info.function, func);
		node->next = NULL;
		insertsymbol(node);
	}
    if(printnote==1)
		printf("end of fundec\n");
}

ParameterList* varlist(TreeNode *p)
{
    if(printnote==1)
		printf("varlist\n");
	ParameterList *param = paramdec(p->children[0]);
	int ret = checksymbol(param->name, 0);
	if (ret != 0)
	{
		//error 3, redefined variable
		printf("Error type 3 at Line %d: redefined variable name: \"%s\".\n", param->linenumber, param->name);
		errorsum++;
	}
	else
	{
		HashNode *node = (HashNode*)malloc(sizeof(HashNode));
		strcpy(node->name, param->name);
		node->typeinfo = (TypeInfo*)malloc(sizeof(TypeInfo));
		copyTypeInfo(node->typeinfo, param->typeinfo);
		node->next = NULL;
		insertsymbol(node);
	}
	if (p->childrennum == 3) //ParamDec COMMA VarList
		param->next = varlist(p->children[2]);
    if(printnote==1)
		printf("end of varlist\n");
	return param;

}

ParameterList* paramdec(TreeNode *p) // Specifier VarDec
{
    if(printnote==1)
		printf("paramdec\n");
	TypeInfo *type = specifier(p->children[0]);
	FieldList *field= vardec(p->children[1], type);
	ParameterList *param = (ParameterList*)malloc(sizeof(ParameterList));
	strcpy(param->name, field->name);
	param->typeinfo = (TypeInfo*)malloc(sizeof(TypeInfo));
	copyTypeInfo(param->typeinfo, field->typeinfo);
    param->linenumber = field->linenumber;
	param->next = NULL;
    if(printnote==1)
		printf("end of paramdec\n");
	return param;
}

void compst(TreeNode *p, TypeInfo *type) //LC DefList StmtList RC
{
    if(printnote==1)
		printf("compst\n");
	funcdeflist(p->children[1]);
	stmtlist(p->children[2], type);
    if(printnote==1)
		printf("end of compst\n");
}

void funcdeflist(TreeNode *p)
{
    if(printnote==1)
		printf("funcdeflist\n");
	if (p == NULL) //empty
    {
        if(printnote==1)
		    printf("end of funcdeflist\n");
        return;
    }
    // Def DefList		
	funcdef(p->children[0]);
	funcdeflist(p->children[1]);
    if(printnote==1)
		printf("end of funcdeflist\n");
}

void funcdef(TreeNode *p) //Specifier DecList SEMI
{
    if(printnote==1)
		printf("funcdef\n");
	TypeInfo *spf = specifier(p->children[0]);
	funcdeclist(p->children[1], spf);
    if(printnote==1)
		printf("end of funcdef\n");
}

void funcdeclist(TreeNode *p, TypeInfo *type)
{
    if(printnote==1)
		printf("funcdeclist\n");
	funcdec(p->children[0], type);
	if(p->childrennum == 3) //Dec COMMA DecList
		funcdeclist(p->children[2], type);
    if(printnote==1)
		printf("end of funcdeclist\n");
}

void funcdec(TreeNode *p, TypeInfo *type)
{
    if(printnote==1)
		printf("funcdec\n");
	FieldList *field = vardec(p->children[0], type);
	if (p->childrennum == 3) //VarDec ASSIGNOP Exp
	{
		TypeInfo *res = Exp(p->children[2]);
		if (isEqualType(res, field->typeinfo) == 0)
		{
			//error 5, mismatched type
			printf("Error type 5 at Line %d: type mismatched for '='.\n", p->children[1]->linenumber);
			errorsum++;
		}
	}
	int ret = checksymbol(field->name, 0);
	if (ret != 0)
	{
		//error 3, redefined variable
		printf("Error type 3 at Line %d: redefined variable name: \"%s\".\n", field->linenumber, field->name);
		errorsum++;
	}
	else
	{
		HashNode *node = (HashNode*)malloc(sizeof(HashNode));
		strcpy(node->name, field->name);
		node->typeinfo = (TypeInfo*)malloc(sizeof(TypeInfo));
		copyTypeInfo(node->typeinfo, field->typeinfo);
		node->next = NULL;
		insertsymbol(node);
	}
    if(printnote==1)
		printf("end of funcdec\n");
}

void stmtlist(TreeNode *p, TypeInfo *type)
{
    if(printnote==1)
		printf("stmtlist\n");
	if(p == NULL)
	{
		if(printnote==1)
			printf("end of stmtlist\n");
		return;
	}
	//Stmt StmtList
	stmt(p->children[0], type);
	stmtlist(p->children[1], type);
    if(printnote==1)
		printf("end of stmtlist\n");
}

void stmt(TreeNode *p, TypeInfo *type)
{
    if(printnote==1)
		printf("stmt\n");
	if(p->childrennum == 1) //CompSt
		compst(p->children[0], type);
	else if(p->childrennum == 2) //Exp SEMI
		Exp(p->children[0]);
	else if(p->childrennum == 3) //RETURN Exp SEMI
	{
		TypeInfo *ret = (TypeInfo*)malloc(sizeof(TypeInfo));
		ret = Exp(p->children[1]);
		if(isEqualType(ret, type) == 0)
		{
			// error 8, mismatched return type
			printf("Error type 8 at Line %d: mismatched return type.\n", p->children[0]->linenumber);
			errorsum++;
		}
	}
	else if(p->childrennum == 5)
	{
		if(strcmp(p->children[0]->contents, "if") == 0) //IF LP Exp RP Stmt
		{
			TypeInfo *res = Exp(p->children[2]);
			if(res->kind != BASIC || res->info.basic != TYPE_INT)
			{
				// error, type in if,while is not int
				//printf("Error type 18 at Line %d: type in statement if() is not int.\n", p->children[0]->linenumber);
				errorsum++;
			}
			stmt(p->children[4], type);
		}
		else //WHILE LP Exp RP Stmt
		{
			TypeInfo *res = Exp(p->children[2]);
			if(res->kind != BASIC || res->info.basic != TYPE_INT)
			{
				// error, type in if,while is not int
				//printf("Error type 18 at Line %d: type in statement while() is not int.\n", p->children[0]->linenumber);
				errorsum++;
			}
			stmt(p->children[4], type);
		}
	}
	else //IF LP Exp RP Stmt ELSE Stmt
	{
		TypeInfo *res = Exp(p->children[2]);
		if(res->kind != BASIC || res->info.basic != TYPE_INT)
		{
			// error, type in if,while is not int
			//printf("Error type 18 at Line %d: type in statement if() is not int.\n", p->children[0]->linenumber);
			errorsum++;
		}
		stmt(p->children[4], type);
		stmt(p->children[6], type);
	}
    if(printnote==1)
		printf("end of stmt\n");
}

TypeInfo* Exp(TreeNode *p)
{
	if(p->childrennum == 1)
	{
		if(strcmp(p->children[0]->type, "ID") == 0)
			return expid(p);
		else if(strcmp(p->children[0]->type, "FLOAT") == 0)
			return expfloat(p);
		else
			return expint(p);
	}
	else if(p->childrennum == 2)
	{
		if (strcmp(p->children[0]->type, "MINUS") == 0)
			return minusexp(p);
		else
			return notexp(p);
	}
	else if(p->childrennum == 3)
	{
		if (strcmp(p->children[0]->type, "LP") == 0)// LP Exp RP
			return Exp(p->children[1]);
		else if (strcmp(p->children[0]->type, "ID") == 0)// ID LP RP
			return callfunc(p);
		else // Exp ...
		{
			if (strcmp(p->children[1]->type, "ASSIGNOP") == 0)
				return expassignop(p);
			else if (strcmp(p->children[1]->type, "AND") == 0 || strcmp(p->children[1]->type, "OR") == 0)
				return expandor(p);
			else if (strcmp(p->children[1]->type, "DOT") == 0)
				return callstruct(p);
			else if (strcmp(p->children[1]->type, "RELOP") == 0)
				return exprelop(p);
			else //PLUS, MINUS, STAR, DIV
				return expcalculate(p);
		}
	}
	else
	{
		if(strcmp(p->children[0]->type, "ID") == 0)// ID LP Args RP
			return callfunc(p);
		else // Exp LB Exp RB
			return callarray(p);
	}
}

TypeInfo* expid(TreeNode *p)
{
	// int ret1 = checksymbol(p->children[0]->contents, 0);
	// int ret2 = checksymbol(p->children[0]->contents, 1);
	// TypeInfo *type = (TypeInfo*)malloc(sizeof(TypeInfo));
	// p->isleftexp = 1; // is left expression
	// if (ret1 == 0 && ret2 == 0)
	// {
	// 	//error 1, undefined variable
	// 	type->kind = ERROR;
	// 	type->info.errortype = 1;
	// 	printf("Error type 1 at Line %d: undefined variable name: \"%s\".\n", p->children[0]->linenumber, p->children[0]->contents);
	// 	errorsum++;
	// }
	// else
	// {
	// 	if(ret2 == 1) //is a function
	// 	{
	// 		HashNode *node = findsymbol(p->children[0]->contents, FUNC);
	// 		copyTypeInfo(type, node->typeinfo);
	// 	}
	// 	else
	// 	{
	// 		HashNode *node = findsymbol(p->children[0]->contents, BASIC);
	// 		if(node == NULL)
	// 			node = findsymbol(p->children[0]->contents, ARRAY);
	// 		if(node == NULL)
	// 			node = findsymbol(p->children[0]->contents, STRUCT);
	// 		copyTypeInfo(type, node->typeinfo);
	// 	}
	// }
	int ret = checksymbol(p->children[0]->contents, 0);
	TypeInfo *type = (TypeInfo*)malloc(sizeof(TypeInfo));
	p->isleftexp = 1; // is left expression
	if(ret == 0)
	{
		//error 1, undefined variable
		type->kind = ERROR;
		type->info.errortype = 1;
		printf("Error type 1 at Line %d: undefined variable name: \"%s\".\n", p->children[0]->linenumber, p->children[0]->contents);
		errorsum++;
	}
	else
	{
		HashNode *node = findsymbol(p->children[0]->contents, BASIC);
		if(node == NULL)
			node = findsymbol(p->children[0]->contents, ARRAY);
		if(node == NULL)
			node = findsymbol(p->children[0]->contents, STRUCT);
		copyTypeInfo(type, node->typeinfo);
	}
	return type;
}

TypeInfo* expfloat(TreeNode *p)
{
	TypeInfo *type = (TypeInfo*)malloc(sizeof(TypeInfo));
	type->kind = BASIC;
	type->info.basic = TYPE_FLOAT;
	p->isleftexp = 0;
	return type;
}

TypeInfo* expint(TreeNode *p)
{
	TypeInfo *type = (TypeInfo*)malloc(sizeof(TypeInfo));
	type->kind = BASIC;
	type->info.basic = TYPE_INT;
	p->isleftexp = 0;
	return type;
}

TypeInfo* minusexp(TreeNode *p)
{
	TypeInfo *type = Exp(p->children[1]);
	p->isleftexp = 0;
	if(type->kind == BASIC)
		return type;
	else
	{
		// error 7, type mismatched for operands
		TypeInfo *error = (TypeInfo*)malloc(sizeof(TypeInfo));
		error->kind = ERROR;
		error->info.errortype = 7;
		printf("Error type 7 at Line %d: operand type doesn't match with operator '-'.\n", p->children[0]->linenumber);
		errorsum++;
		return error;
	}
}

TypeInfo* notexp(TreeNode *p)
{
	TypeInfo *type = Exp(p->children[1]);
	p->isleftexp = 0;
	if (type->kind == BASIC && type->info.basic == TYPE_INT)
		return type;
	else
	{
		// error 7, type mismatched for operands
		TypeInfo *error = (TypeInfo*)malloc(sizeof(TypeInfo));
		error->kind = ERROR;
		error->info.errortype = 7;
		printf("Error type 7 at Line %d: operand type doesn't match with operator '!'.\n", p->children[0]->linenumber);
		errorsum++;
		return error;
	}
}

TypeInfo* callfunc(TreeNode *p) // ID LP Args RP | ID LP RP
{
	TypeInfo *type = (TypeInfo*)malloc(sizeof(TypeInfo));
	int ret1 = checksymbol(p->children[0]->contents, 1);
	int ret2 = checksymbol(p->children[0]->contents, 0);
	p->isleftexp = 0;
	if(ret1 == 0)
	{
		type->kind = ERROR;
		if(ret2 == 1)
		{
			// error 11, not a function
			type->info.errortype = 11;
			printf("Error type 11 at Line %d: \"%s\" is not a function.\n", p->children[0]->linenumber, p->children[0]->contents);
		}
		else
		{
			// error 2, undefined function
			type->info.errortype = 2;
			printf("Error type 2 at Line %d: undefined function name: \"%s\".\n", p->children[0]->linenumber, p->children[0]->contents);
		}
		errorsum++;
	}
	else
	{
		HashNode *node = findsymbol(p->children[0]->contents, FUNC);
		if(p->childrennum == 3) // ID LP RP
		{
			if(node->typeinfo->info.function->paranum == 0)
				copyTypeInfo(type, node->typeinfo->info.function->functype);
			else
			{
				// error 9, arguments wrong
				// type->kind = ERROR;
				// type->info.errortype = 9;
				copyTypeInfo(type, node->typeinfo->info.function->functype);
				printf("Error type 9 at Line %d: function: \"%s\" is not applicable for the arguments.\n", p->children[0]->linenumber, p->children[0]->contents);
				errorsum++;
			}
		}
		else // ID LP Args RP
		{
			if(node->typeinfo->info.function->paranum > 0 && args(p->children[2], node->typeinfo->info.function->paralist) == 1)
				copyTypeInfo(type, node->typeinfo->info.function->functype);
			else
			{
				// error 9, arguments wrong
				// type->kind = ERROR;
				// type->info.errortype = 9;
				copyTypeInfo(type, node->typeinfo->info.function->functype);
				printf("Error type 9 at Line %d: function: \"%s\" is not applicable for the arguments.\n", p->children[0]->linenumber, p->children[0]->contents);
				errorsum++;
			}
		}
	}
	return type;
}

int args(TreeNode *p, ParameterList *param)
{
	TreeNode *q = p;
	ParameterList *pa = param;
	for(; q->childrennum>1; q=q->children[2], pa=pa->next)
	{
		if(pa == NULL)
			return 0;	
		TypeInfo *type = Exp(q->children[0]);
		if(isEqualType(type, pa->typeinfo) == 0)
			return 0;
	}
	if(pa == NULL)
		return 0;
	if(pa->next != NULL)
		return 0;
	TypeInfo *t = Exp(q->children[0]);
	if(isEqualType(t, pa->typeinfo) == 0)
		return 0;
	return 1;
}

TypeInfo* expassignop(TreeNode *p)
{
	TypeInfo *type1 = Exp(p->children[0]);
	TypeInfo *type2 = Exp(p->children[2]);
	p->isleftexp = 0; //exp -> exp1 = exp2, exp is not a LEFT expression
	if(isEqualType(type1, type2) == 0)
	{
		//error 5, mismatched type
		TypeInfo *error = (TypeInfo*)malloc(sizeof(TypeInfo));
		error->kind = ERROR;
		error->info.errortype = 5;
		printf("Error type 5 at Line %d: type mismatched for '='.\n", p->children[1]->linenumber);
		errorsum++;
		return error;
	}
	else
	{
		if(p->children[0]->isleftexp == 1)
			return type1;
		else
		{
			// error 6, leftside is not a variable
			TypeInfo *error = (TypeInfo*)malloc(sizeof(TypeInfo));
			error->kind = ERROR;
			error->info.errortype = 6;
			printf("Error type 6 at Line %d: the left-hand side of an assignment must be a variable.\n", p->children[0]->linenumber);
			errorsum++;
			return error;
		}
	}
}

TypeInfo* expandor(TreeNode *p)
{
	TypeInfo *type1 = Exp(p->children[0]);
	TypeInfo *type2 = Exp(p->children[2]);
	p->isleftexp = 0;
	if(type1->kind == BASIC && type1->info.basic == TYPE_INT && isEqualType(type1, type2)==1)
		return type1;
	else
	{
		// error 7, type mismatched for operands
		TypeInfo *error = (TypeInfo*)malloc(sizeof(TypeInfo));
		error->kind = ERROR;
		error->info.errortype = 7;
		printf("Error type 7 at Line %d: operands type mismatched between the operator \"%s\".\n", p->children[1]->linenumber, p->children[1]->contents);
		errorsum++;
		return error;
	}
}

TypeInfo* exprelop(TreeNode *p)
{
	TypeInfo *type1 = Exp(p->children[0]);
	TypeInfo *type2 = Exp(p->children[2]);
	p->isleftexp = 0;
	if(type1->kind == BASIC && isEqualType(type1, type2) == 1) //result type of relop is int
	{
		TypeInfo *type = (TypeInfo*)malloc(sizeof(TypeInfo));
		type->kind = BASIC;
		type->info.basic = TYPE_INT;
		return type;
	}
	else
	{
		// error 7, type mismatched for operands
		TypeInfo *error = (TypeInfo*)malloc(sizeof(TypeInfo));
		error->kind = ERROR;
		error->info.errortype = 7;
		printf("Error type 7 at Line %d: operands type mismatched between the operator \"%s\".\n", p->children[1]->linenumber, p->children[1]->contents);
		errorsum++;
		return error;
	}
}

TypeInfo* expcalculate(TreeNode *p)
{
	TypeInfo *type1 = Exp(p->children[0]);
	TypeInfo *type2 = Exp(p->children[2]);
	p->isleftexp = 0;
	if(type1->kind == BASIC && isEqualType(type1, type2)==1)
		return type1;
	else
	{
		// error 7, type mismatched for operands
		TypeInfo *error = (TypeInfo*)malloc(sizeof(TypeInfo));
		error->kind = ERROR;
		error->info.errortype = 7;
		printf("Error type 7 at Line %d: operands type mismatched between the operator \"%s\".\n", p->children[1]->linenumber, p->children[1]->contents);
		errorsum++;
		return error;
	}
}

TypeInfo* callstruct(TreeNode *p) // Exp DOT ID
{
	TypeInfo *type = Exp(p->children[0]);
	p->isleftexp = 1; // is left expression
	if (type->kind != STRUCT)
	{
		// error 13, variable is not a struct
		TypeInfo *error = (TypeInfo*)malloc(sizeof(TypeInfo));
		error->kind = ERROR;
		error->info.errortype = 13;
		printf("Error type 13 at Line %d: illegal use of \".\".\n", p->children[1]->linenumber);
		errorsum++;
		return error;
	}
	else
	{
		int find = 0;
		FieldList *field = type->info.structure;
		for(; field != NULL; field=field->next)
		{
			if(strcmp(field->name, p->children[2]->contents) == 0)
			{
				find = 1;
				break;
			}
		}
		if(find == 0)
		{
			// error 14, visit non-existent field
			TypeInfo *error = (TypeInfo*)malloc(sizeof(TypeInfo));
			error->kind = ERROR;
			error->info.errortype = 14;
			printf("Error type 14 at Line %d: visit non-exsit structure's field: \"%s\".\n", p->children[2]->linenumber, p->children[2]->contents);
			errorsum++;
			return error;
		}
		else
		{
			TypeInfo *fieldtype = (TypeInfo*)malloc(sizeof(TypeInfo));
			copyTypeInfo(fieldtype, field->typeinfo);
			return fieldtype;
		}
	}
}

TypeInfo* callarray(TreeNode *p)
{
	TypeInfo *type = Exp(p->children[0]);
	TypeInfo *index = Exp(p->children[2]);
	p->isleftexp = 1; // is left expression
	if (type->kind != ARRAY)
	{
		// error 10, variable is not an array
		TypeInfo *error = (TypeInfo*)malloc(sizeof(TypeInfo));
		error->kind = ERROR;
		error->info.errortype = 10;
		printf("Error type 10 at Line %d: illegal use of \"[]\".\n", p->children[1]->linenumber);
		errorsum++;
		return error;
	}
	else
	{
		if (index->kind != BASIC || index->info.basic != TYPE_INT)
		{
			// error 12, variable in [] is not an integer
			TypeInfo *error = (TypeInfo*)malloc(sizeof(TypeInfo));
			error->kind = ERROR;
			error->info.errortype = 12;
			printf("Error type 12 at Line %d: array argument is not an integer.\n", p->children[2]->linenumber);
			errorsum++;
			return error;
		}
		else
		{
			TypeInfo *innertype = (TypeInfo*)malloc(sizeof(TypeInfo));
			copyTypeInfo(innertype, type->info.array.element);
			return innertype;
		}
	}
}
