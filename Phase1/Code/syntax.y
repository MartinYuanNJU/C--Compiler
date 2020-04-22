%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "lex.yy.c"
	#include "tree.h"
	extern int yylineno;
	extern TreeNode* root;
	extern int errorsum;
	void yyerror(char *info);
	int errorpos[2049] = {0};
%}

%union {
	struct TreeNode* node;
}

%token <node> INT FLOAT ID SEMI COMMA ASSIGNOP RELOP PLUS
%token <node> MINUS STAR DIV AND OR DOT NOT TYPE LP RP
%token <node> LB RB LC RC STRUCT RETURN IF ELSE WHILE

%right ASSIGNOP  
%left OR 
%left AND 
%left RELOP
%left PLUS MINUS 
%left STAR DIV
%right NOT
%nonassoc NEG
%left LP RP LB RB DOT

%type <node> Program ExtDefList ExtDef ExtDecList Specifier StructSpecifier OptTag Tag VarDec 
%type <node> FunDec VarList ParamDec CompSt StmtList Stmt DefList Def DecList Dec Exp Args

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Program : ExtDefList				          {$$=createNode("nonterminal","Program",@$.first_line);addNode($$,$1);root=$$;}
		;

ExtDefList	: ExtDef ExtDefList			      {$$=createNode("nonterminal","ExtDefList",@$.first_line);addNode($$,$1);addNode($$,$2);}
			| /*empty*/				          {$$=NULL;}
			;

ExtDef	: Specifier ExtDecList SEMI		      {$$=createNode("nonterminal","ExtDef",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Specifier SEMI			          {$$=createNode("nonterminal","ExtDef",@$.first_line);addNode($$,$1);addNode($$,$2);}
		| Specifier FunDec CompSt		      {$$=createNode("nonterminal","ExtDef",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Specifier ExtDecList {
			if(errorpos[@2.last_line] == 0)
			{
				printf("Error type B at line %d: Syntax error.\n", @2.last_line);
				errorsum++;
				errorpos[@2.last_line]++;
				
			}
		}
		| Specifier {
			if(errorpos[@1.last_line] == 0)
			{
				printf("Error type B at line %d: Syntax error.\n", @1.last_line);
				errorsum++;
				errorpos[@1.last_line]++;
				
			}
		}
		| Specifier error SEMI {
			if(errorpos[@2.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @2.first_line, @3.first_line);
				errorsum++;
				errorpos[@2.first_line]++;
				
			}
		}
		| error FunDec CompSt {
			if(errorpos[@1.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error.\n", @1.first_line);
				errorsum++;
				errorpos[@1.first_line]++;
				
			}
		}
		;

ExtDecList	: VarDec				          {$$=createNode("nonterminal","ExtDecList",@$.first_line);addNode($$,$1);}
			| VarDec COMMA ExtDecList		  {$$=createNode("nonterminal","ExtDecList",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
			;

Specifier	: TYPE					          {$$=createNode("nonterminal","Specifier",@$.first_line);addNode($$,$1);}
			| StructSpecifier			      {$$=createNode("nonterminal","Specifier",@$.first_line);addNode($$,$1);}
			;

StructSpecifier	: STRUCT OptTag LC DefList RC {$$=createNode("nonterminal","StructSpecifier",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);addNode($$,$4);addNode($$,$5);}
				| STRUCT Tag				  {$$=createNode("nonterminal","StructSpecifier",@$.first_line);addNode($$,$1);addNode($$,$2);}
				| STRUCT error RC {
					if(errorpos[@2.first_line] == 0)
					{
						
						printf("Error type B at line %d: Syntax error, before \"}\" at line %d.\n", @2.first_line, @3.first_line);
						errorsum++;
						errorpos[@2.first_line]++;
						yyerrok;
					}
				}
				| error OptTag LC DefList RC {
					if(errorpos[@1.first_line] == 0)
					{
						
						printf("Error type B at line %d: Syntax error, near \"{\" at line %d.\n", @1.first_line, @3.first_line);
						errorsum++;
						errorpos[@1.first_line]++;
						yyerrok;
					}
				}
				;

OptTag	: ID					              {$$=createNode("nonterminal","OptTag",@$.first_line);addNode($$,$1);}
		| /*empty*/				              {$$=NULL;}
		;

Tag		: ID					              {$$=createNode("nonterminal","Tag",@$.first_line);addNode($$,$1);}
		;
	
VarDec	: ID					              {$$=createNode("nonterminal","VarDec",@$.first_line);addNode($$,$1);}
		| VarDec LB INT RB			          {$$=createNode("nonterminal","VarDec",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);addNode($$,$4);}
		| VarDec LB error RB {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, between \"[\" at line %d and \"]\" at line %d.\n",@3.first_line, @2.first_line, @4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
			}
		}
		;

FunDec	: ID LP VarList RP			          {$$=createNode("nonterminal","FunDec",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);addNode($$,$4);}
		| ID LP RP				              {$$=createNode("nonterminal","FunDec",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| ID LP error RP {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, between \"(\" at line %d and \")\" at line %d.\n",@3.first_line, @2.first_line, @4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
			}
		}
		;
		
VarList	: ParamDec COMMA VarList		      {$$=createNode("nonterminal","VarList",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| ParamDec				              {$$=createNode("nonterminal","VarList",@$.first_line);addNode($$,$1);}
		;

ParamDec: Specifier VarDec			          {$$=createNode("nonterminal","ParamDec",@$.first_line);addNode($$,$1);addNode($$,$2);}
		;

CompSt	: LC DefList StmtList RC		      {$$=createNode("nonterminal","CompSt",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);addNode($$,$4);}
		| LC error RC {
			if(errorpos[@2.first_line] == 0)
			{
				printf("Error type B at line %d: Syntax error, between \"{\" at line %d and \"}\" at line %d.\n",@2.first_line, @1.first_line, @3.first_line);
				errorsum++;
				errorpos[@2.first_line]++;
				
			}
		}
		| LC DefList StmtList {
			if(errorpos[@3.last_line] == 0)
			{
				printf("Error type B at line %d: Syntax error.\n", @3.last_line);
				errorsum++;
				errorpos[@3.last_line]++;
				
			}
		}
		;

StmtList: Stmt StmtList				          {$$=createNode("nonterminal","StmtList",@$.first_line);addNode($$,$1);addNode($$,$2);}
		| /*empty*/				              {$$=NULL;}
		;

Stmt	: Exp SEMI				              {$$=createNode("nonterminal","Stmt",@$.first_line);addNode($$,$1);addNode($$,$2);}
		| CompSt				              {$$=createNode("nonterminal","Stmt",@$.first_line);addNode($$,$1);}
		| RETURN Exp SEMI			          {$$=createNode("nonterminal","Stmt",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {$$=createNode("nonterminal","Stmt",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);addNode($$,$4);addNode($$,$5);}
		| IF LP Exp RP Stmt ELSE Stmt		  {$$=createNode("nonterminal","Stmt",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);addNode($$,$4);addNode($$,$5);addNode($$,$6);addNode($$,$7);}
		| IF error ELSE Stmt {
			if(errorpos[@2.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error before \"else\" at line %d\n.", @2.first_line, @3.first_line);
				errorsum++;
				errorpos[@2.first_line]++;
				
			}
		}
		| WHILE LP Exp RP Stmt			      {$$=createNode("nonterminal","Stmt",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);addNode($$,$4);addNode($$,$5);}
		| WHILE error RP Stmt {
			if(errorpos[@2.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error before \")\" at line %d\n.", @2.first_line, @3.first_line);
				errorsum++;
				errorpos[@2.first_line]++;
				
			}	
		}
		| WHILE error RP {
			if(errorpos[@2.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error before \")\" at line %d\n.", @2.first_line, @3.first_line);
				errorsum++;
				errorpos[@2.first_line]++;
				
			}	
		}
		| RETURN error SEMI {
			if(errorpos[@2.first_line] == 0)
			{
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @2.first_line, @3.first_line);
				errorsum++;
				errorpos[@2.first_line]++;
				
			}
		}
		| RETURN Exp {
			if(errorpos[@2.last_line] == 0)
			{
				printf("Error type B at line %d: Syntax error.\n", @2.last_line);
				errorsum++;
				errorpos[@2.last_line]++;
				
			}
		}
		| error SEMI {
			if(errorpos[@1.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @1.first_line, @2.first_line);
				errorsum++;
				errorpos[@1.first_line]++;
				
			}
		}
		| Exp error {
			if(errorpos[@1.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error.\n", @2.first_line);
				errorsum++;
				errorpos[@2.first_line]++;
				
			}
		}
		;

DefList	: Def DefList				          {$$=createNode("nonterminal","DefList",@$.first_line);addNode($$,$1);addNode($$,$2);}
		| /*empty*/				              {$$=NULL;}
		;

Def		: Specifier DecList SEMI		      {$$=createNode("nonterminal","Def",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Specifier error SEMI {
			if(errorpos[@2.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @2.first_line, @3.first_line);
				errorsum++;
				errorpos[@2.first_line]++;
				
			}
		}
		| error DecList SEMI {
			if(errorpos[@1.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error.\n", @1.first_line);
				errorsum++;
				errorpos[@1.first_line]++;
				
			}
		}
		| Specifier DecList {
			if(errorpos[@2.last_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error.\n", @2.last_line);
				errorsum++;
				errorpos[@2.last_line]++;
				
			}
		}
		;

DecList	: Dec					              {$$=createNode("nonterminal","DecList",@$.first_line);addNode($$,$1);}
		| Dec COMMA DecList			          {$$=createNode("nonterminal","DecList",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		;

Dec		: VarDec				              {$$=createNode("nonterminal","Dec",@$.first_line);addNode($$,$1);}
		| VarDec ASSIGNOP Exp			      {$$=createNode("nonterminal","Dec",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}

Exp		: Exp ASSIGNOP Exp			          {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Exp AND Exp				          {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Exp OR Exp				          {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Exp RELOP Exp				          {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Exp PLUS Exp				          {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Exp MINUS Exp				          {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Exp STAR Exp				          {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Exp DIV Exp				          {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| LP Exp RP				              {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| MINUS Exp	%prec NEG			      {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);}
		| NOT Exp				              {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);}
		| ID LP Args RP				          {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);addNode($$,$4);}
		| ID LP RP				              {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Exp LB Exp RB				          {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);addNode($$,$4);}
		| Exp DOT ID		                  {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| ID			                      {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);}
		| INT			                      {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);}
		| FLOAT			                      {$$=createNode("nonterminal","Exp",@$.first_line);addNode($$,$1);}
		| Exp ASSIGNOP error SEMI {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @3.first_line, @4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
			}
		}
		| Exp AND error SEMI {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @3.first_line, @4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
			}
		}
		| Exp OR error SEMI {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @3.first_line, @4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
			}
		}
		| Exp RELOP error SEMI {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @3.first_line, @4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
			}
		}
		| Exp PLUS error SEMI {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @3.first_line, @4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
			}
		}
		| Exp MINUS error SEMI {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @3.first_line, @4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
			}
		}
		| Exp STAR error SEMI {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @3.first_line, @4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
			}
		}
		| Exp DIV error SEMI {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @3.first_line, @4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
			}
		}
		| MINUS error SEMI {
			if(errorpos[@2.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @2.first_line, @3.first_line);
				errorsum++;
				errorpos[@2.first_line]++;
				
			}
		}
		| NOT error SEMI {
			if(errorpos[@2.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, before \";\" at line %d.\n", @2.first_line, @3.first_line);
				errorsum++;
				errorpos[@2.first_line]++;
				
			}
		}
		| ID LP error SEMI {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, after \"(\" at line %d.\n", @3.first_line, @2.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
				
			}
		}
		| ID LP error RP {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, between \"(\" at line %d and \")\" at line %d.\n", @3.first_line, @2.first_line,@4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
			}
		}
		| Exp LB error RB {
			if(errorpos[@3.first_line] == 0)
			{
				
				printf("Error type B at line %d: Syntax error, between \"[\" at line %d and \"]\" at line %d.\n", @3.first_line, @2.first_line,@4.first_line);
				errorsum++;
				errorpos[@3.first_line]++;
				
			}
		}
		;

Args	: Exp COMMA Args	                  {$$=createNode("nonterminal","Args",@$.first_line);addNode($$,$1);addNode($$,$2);addNode($$,$3);}
		| Exp			                      {$$=createNode("nonterminal","Args",@$.first_line);addNode($$,$1);}
		;

%%
void yyerror(char *info) {
	errorsum++;
}
