%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "syntax.tab.h"
	#include "tree.h"
	extern int errorsum;
	int yycolumn = 1;
	extern int errorpos[2049];
  	#define YY_USER_ACTION \
   		yylloc.first_line = yylloc.last_line = yylineno; \
   		yylloc.first_column = yycolumn; \
   		yylloc.last_column = yycolumn + yyleng - 1; \
   		yycolumn += yyleng;
%}

%option yylineno

INT 0|([1-9][0-9]*)
FLOAT [0-9]+\.[0-9]+
ID [a-zA-Z_][a-zA-Z_0-9]*
SEMI ;
COMMA ,
ASSIGNOP =
RELOP >|<|>=|<=|==|!=
PLUS "+"
MINUS "-"
STAR "*"
DIV "/"
AND "&&"
OR "||"
DOT "."
NOT "!"
TYPE int|float
LP "("
RP ")"
LB "["
RB "]"
LC "{"
RC "}"
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while
SINGLEANNOTATE "//"
MULTIANNOTATE "/*"
SPACE [ \t\r]+
LINEFEED \n
UNKNOWN .
ERRORARROW "->"

%%
{TYPE} {
	//printf("TYPE %s\n", yytext);
	yylval.node=createNode("TYPE",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return TYPE;
}
{STRUCT} {
	//printf("STRUCT\n");
	yylval.node=createNode("STRUCT",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return STRUCT;
}

{RETURN} {
	//printf("RETURN\n");
	yylval.node=createNode("RETURN",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return RETURN;
}
{IF} {
	//printf("IF\n");
	yylval.node=createNode("IF",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return IF;	
}
{ELSE} {
	//printf("ELSE\n");
	yylval.node=createNode("ELSE",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return ELSE;
}
{WHILE} {
	//printf("WHILE\n");
	yylval.node=createNode("WHILE",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return WHILE;	
}

{INT} {
	//printf("INT %d\n", atoi(yytext));
	yylval.node=createNode("INT",yytext,yylineno);
	//yylval.int_value = atoi(yytext);
	return INT;
}
{FLOAT} {
	//printf("FLOAT %f\n", atof(yytext));
	yylval.node=createNode("FLOAT",yytext,yylineno);
	//yylval.float_value = atof(yytext);
	return FLOAT;
}
{ID} {
	//printf("ID %s\n", yytext);
	yylval.node=createNode("ID",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return ID;
}
{SEMI} {
	//printf("SEMI\n");
	yylval.node=createNode("SEMI",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return SEMI;	
}
{COMMA} {
	//printf("COMMA\n");
	yylval.node=createNode("COMMA",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return COMMA;
}
{ASSIGNOP} {
	//printf("ASSIGNOP\n");
	yylval.node=createNode("ASSIGNOP",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return ASSIGNOP;
}
{RELOP} {
	//printf("RELOP\n");
	yylval.node=createNode("RELOP",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return RELOP;
}
{PLUS} {
	//printf("PLUS\n");
	yylval.node=createNode("PLUS",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return PLUS;
}
{MINUS} {
	//printf("MINUS\n");
	yylval.node=createNode("MINUS",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return MINUS;
}
{STAR} {
	//printf("STAR\n");
	yylval.node=createNode("STAR",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return STAR;
}
{DIV} {
	//printf("DIV\n");
	yylval.node=createNode("DIV",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return DIV;
}
{AND} {
	//printf("AND\n");
	yylval.node=createNode("AND",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return AND;
}
{OR} {
	//printf("OR\n");
	yylval.node=createNode("OR",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return OR;
}
{DOT} {
	//printf("DOT\n");
	yylval.node=createNode("DOT",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return DOT;
}
{NOT} {
	//printf("NOT\n");
	yylval.node=createNode("NOT",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return NOT;
}
{LP} {
	//printf("LP\n");
	yylval.node=createNode("LP",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return LP;	
}
{RP} {
	//printf("RP\n");
	yylval.node=createNode("RP",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return RP;
}
{LB} {
	//printf("LB\n");
	yylval.node=createNode("LB",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return LB;	
}
{RB} {
	//printf("RB\n");
	yylval.node=createNode("RB",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return RB;
}
{LC} {
	//printf("LC\n");
	yylval.node=createNode("LC",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return LC;
}
{RC} {
	//printf("RC\n");
	yylval.node=createNode("RC",yytext,yylineno);
	//strcpy(yylval.str, yytext);
	return RC;
}
{SPACE} {/*do nothing*/}
{LINEFEED} {yycolumn = 1;}

{SINGLEANNOTATE} {char c = input(); while ((c != '\n') && (c != EOF)) c = input();}
{MULTIANNOTATE} {
	char c;
	int hasstar = 0;
	while(1)
	{
		c = input();
		if(c == EOF)
		{
			errorsum++; 
			printf("Error type B at line %d: no \"*/\" match with \"/*\".\n", yylineno);
			errorpos[yylineno]++;
			break;
		}
		if(hasstar == 0)
		{
			if(c == '*')
				hasstar = 1;
		}
		else
		{
			if(c == '*')
				hasstar = 1;
			else if(c == '/')
				break; //matched
			else
				hasstar = 0;
		}	
	}
}

{UNKNOWN} {
	errorsum++; 
	printf("Error type A at line %d: Mysterious character \"%s\".\n",yylineno,yytext);
	errorpos[yylineno]++;
}

{ERRORARROW} {
	errorsum++; 
	printf("Error type B at line %d: Syntax error.\n",yylineno);
	errorpos[yylineno]++;
}

%%
int yywrap()
{
	return 1;
}
